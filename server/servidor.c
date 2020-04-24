#include "servidor.h"

int contador;
//Estructura necesaria para acceso excluyente
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;



void *AtenderCliente (void *args_void){
	
	struct thread_args * args = args_void;
	int suser = args->a;
	int i;// laco vetor sockets
	int * vetsockets; // ponteiro vetor sockets
	node ** lista = args->lista;
	mostra(*lista);
	int * tamanho = args->tam;
	int alterlista = 0;
	
	char peticion[512];
	char respuesta[512];
	int ret;

	int logado=0;
	int terminar =0;
	int situacao=0;
	
	MYSQL *conn;
	conn=mysql_init(NULL);
	
	if(conn==NULL){
		printf("Error ao criar conexao: %u %s\n",mysql_errno(conn), mysql_error(conn));
		exit (1);
	}
	
	
	conn=mysql_real_connect(conn,SERVIDORDADOS,USUARIO,SENHA,BASE,0, NULL, 0);
	
	if(conn==NULL){
		printf("Erro ao iniciar conexao: %u%s\n",mysql_errno(conn),mysql_error(conn));
		exit(1);
	}
	
	
	// Laco para atender todas as peticoes desse cliente
	while (terminar ==0){
		
		// Ahora recibimos la petici?n
		ret=read(suser, peticion, sizeof(peticion));
		printf ("Recibido\n");
		
		// Tenemos que anadirle la marca de fin de string 
		// para que no escriba lo que hay despues en el buffer
		peticion[ret]='\0';
		
		
		printf ("Peticion: %s\n",peticion);
		
		// vamos a ver que quieren
		char *p = strtok( peticion, "/");
		int codigo =  atoi (p);
		// Ya tenemos el c?digo de la petici?n
		char nombre[20];
		
		// Se estiver logado pega os dados do mesmo jeito ao desconectar
		if (codigo !=0){
			
			p = strtok( NULL, "/");
			strcpy (nombre, p);
			// Ya tenemos el nombre
			printf ("Codigo: %d, Nome: %s\n", codigo, nombre);
		}
		
		if(codigo ==0){ // Solicita sair
			
			// Se esta logado desloga
			if(logado){
				p = strtok( NULL, "/");
				strcpy(nombre, p);	
				elimina(lista, nombre,tamanho);
				// Atualizar
				alterlista = 1;
				
				
				mostra(*lista);
				logado=0;
			}
			
			terminar=1;
			
		}else if (codigo==1){ // Solicita login servico login = 1/
			
			printf("SOlicitou login");
			char senha[20];
			p = strtok( NULL, "/");
			int situacao=0;
			strcpy(senha, p);
			char *asenha = malloc((MD5_DIGEST_LENGTH*2+1)*sizeof( char));
			asenha = smd5(senha,asenha);
			
			printf("%s\n",asenha);
			
			// Nao existe
			if (busca(*lista, nombre) != NULL){
				
				
				sprintf (respuesta, "4%s",nombre);
				
				
			}else{ // Existe faz tudo normal
				
				// Se usuario ja existe na lista nao pode logar de novo
				situacao=loga_user(nombre,asenha,conn);
				
				if (situacao == 1){ // Login correto
					logado=1;
					
					// 
					//insere(&args->lista, args->a, nombre);
					insere(lista, suser, nombre,tamanho);
					
					printf("Mostra aqui\n");
					// Atualizar
					alterlista = 1;
					// Mostra
					mostra(*lista);
					//mostra(args->lista);
					
					sprintf (respuesta, "1/1%s",nombre); 
				}else if (situacao == 3){  // Credenciais errados
					sprintf (respuesta, "1/2%s",nombre);
				}else if (situacao == 0){ // Erro ao logar
					sprintf (respuesta, "1/0%s",nombre);
				}else{ // Erro ao logar
					
					sprintf (respuesta, "1/3%s",nombre);
				}
				
				
			}
			
			free(asenha);
			
		}else if(codigo==2){ // Solicita deslogar servico = 2/
			printf("Solicitou deslogar");
			char senha[20];
			p = strtok( NULL, "/");
			int situacao=0;
			strcpy(senha, p);
			
			elimina(lista, nombre,tamanho);
			
			// Atualizar
			alterlista = 1;
			
			mostra(*lista);
			
			logado=0;
			
			sprintf(respuesta, "2/0%s",nombre); // Login correto
			
		}else if(codigo==3){ // Solicita excluir USUARIO servico = 3/

			// Somente se estiver logado
			if(logado){
				situacao=remove_user(nombre,conn);
				if(situacao == 1){
					sprintf(respuesta,"3/1%s",nombre); // Deletado corretamente
					elimina(lista, nombre,tamanho);
					mostra(*lista);
					logado=0;
				}else if(situacao == 2){
					sprintf(respuesta,"3/2%s",nombre); // Erro ao excluir
				}
			}else{ // Praticamente impossivel de cair nesse caso
				sprintf(respuesta,"3/3%s",nombre); // Erro ao excluir
			}
			
		}else if (codigo==5){ // insere USUARIO servico = 5/
			
			char senha[20];
			p = strtok( NULL, "/");
			strcpy(senha, p);
			
			char *hsenha = malloc((MD5_DIGEST_LENGTH*2+1)*sizeof( char));
			
			hsenha = smd5(senha,hsenha);
			
			printf("%s\n",hsenha);
			
			
			situacao=insere_user(nombre,hsenha,conn);
			
			if(situacao == 1){
				sprintf(respuesta,"5/1%s",nombre); // Inserido correto
			}else if(situacao == 2){
				sprintf(respuesta,"5/2%s",nombre); // Usuario ja existe
			}else{
				sprintf(respuesta,"5/3%s",nombre); // Erro ao inserir
			}
			
			free(hsenha);
			
		}
		
		if(codigo !=0){ // Desconectar
			printf ("Resposta: %s\n", respuesta);
			// Enviamos a resposta
			write(suser,respuesta, strlen(respuesta));
			
		}if ((codigo == 0)||(codigo == 1)||(codigo== 2)||(codigo== 3)||(codigo== 5)){
			
			pthread_mutex_lock( &mutex ); // No me interrumpas ahora
			contador += 1;
			pthread_mutex_unlock( &mutex ); // Ya puedes interrumpirme
			
			
			
			if(alterlista && *tamanho>0){
				
				printf("String conectados\n");
				char * novo = (char *)malloc(MAXNOME*MAXELE*sizeof(char)+SEPARADOR*sizeof(char));
				
				conectados(*lista, novo,tamanho);
				
				printf("\n%s\n",novo);
				
				vetsockets = vetorSocket(*lista,tamanho);
				
				char notificacion[MAXNOME*MAXELE+2];
				
				sprintf(notificacion, "4/%s",novo);
				
				if(vetorSocket){ // Nao vazio
					for(i=0;i<*tamanho;i++){
						
						
						// Aqui notificaria todos os conectados menos a pessoa que sofreu alteracao
						//if(vetsockets[i] != suser){
						printf("USUARIOS CONECTADOS STRING = %s \n",notificacion);
						write(vetsockets[i],notificacion, strlen(notificacion));
						
						//}
						printf("vetsockets p%d = %d \n",i,vetsockets[i]);
						
						
					}
				}else{
					printf("Vetor sockets vazio\n\n");
				}
				free(vetsockets);
				free(novo);
				alterlista=0;
			}
			
		}
		
		
		// Verifica se teve alguma alteracao, se sim envia para todos os conectados
		
		// Se teve alguma alteracao
		// Servico 6 notificacao

	}
	// Se acabo el servicio para este cliente
	close(suser); 
	mysql_close (conn);
	
}
