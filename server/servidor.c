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
					alterlista = 1;
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
			
		}else if(codigo==6){ // insere USUARIO servico = 6/quemChamou/quantidade/invitado1/invitado2/invitado3...
			
			printf("Codigo 6\n");
			int i = 0;
			
			unsigned int idgame = 0;
			
			
			char qjugador[5];
			p = strtok( NULL, "/");
			strcpy(qjugador, p);
			
			int qjugadores =  atoi(qjugador);
			printf("Quantidade de jogadores = %d",qjugadores);
			char convidado[TAMUSERNAME];
			// Ya tenemos el nombre
			
			// Cria partida insere quem convidou e faz loop com os outros
			// Cria partida e devolve id
			idgame=cria_partida(conn);
			// Ate aqui ja tenho quem criou o jogo
			// Agora relaciono o criador do jogo
			printf("Nome de quem solicitou = %s\n",nombre); 
			
			relaciona_jugador(conn, nombre, idgame);
			// Adiciona quantidade de jogadores
			
			node * usuario = busca(*lista, nombre);
			usuario->emjogo=0; // So vai entrar em jogo ate ficar completo
			usuario->jugadores_partida=qjugadores+1; // 
			usuario->jugadores_momento=1;
			usuario->partida=idgame;
			// A cada resposta altera osvalores de quem criou a partida
			
			
			// Se alguem nao aceita deleta tudo relacionado ao jogo
			
			
			// 6/quemchamou/idgame
			char conviteres[MAXNOME+10];
			sprintf(conviteres, "6/%s/%u",nombre,idgame);
			
			for(i=0;i<qjugadores;i++){
				
				p = strtok( NULL, "/");
				strcpy(convidado, p);
				
				// Envia para todos os jogadores convidados
				
				printf("Convidado %d = %s\n",i,convidado);
				// Enviar convite para os convidados
				write(getsocket(*lista,convidado),conviteres, strlen(conviteres));
				
			}
			
			// atriubi a idgame no usuario que convidou
			// Criar variavel com quantiade de pessoas que foram convidadas tambem
			// vai descontanto ate faltar zero para iniciar
			
			// Aqui envia que ja esta na partida e que os convites foram enviados
			sprintf(respuesta,"7/1%s",nombre);
			// Convida os outros da partida
			
			// Antes de convidar para testar vou tentar fazer um loop
			
			// Faz um for com a quantidade de convidados e envia:
			// 6/quemchamou/idpartida
			
		}else if(codigo==7){ // resposta convite partida = 6/quemChamou/quantidade/invitado1/invitado2/invitado3...
			
			printf("Codigo 7\n");
			// 7/nombre/1/donopartida/idgame
			// aqui vai sobrar somente  /1/donopartida/idgame
			
			char respconvite[2];
			p = strtok( NULL, "/");
			strcpy(respconvite, p);
			int respconvites = atoi(respconvite);
			printf("Reposta convite game = %d",respconvites);
			// Trim o dono da partida
			char donopartida[MAXNOME+1];
			p = strtok( NULL, "/");
			strcpy(donopartida, p);
			
			
			// Seleciona o id da partida
			char idbdgame[10];
			p = strtok( NULL, "/");
			strcpy(idbdgame, p);
			unsigned int idbdgames = atoi(idbdgame);
			// verifica se existe uma partida com essa id (fazer depois)
			printf("Nome de quem respondeu = %s\n",nombre); 
			printf("Nome do dono da partida = %s\n",donopartida); 
			node * usuario = busca(*lista, donopartida);
			
			
			if(respconvites == 1){ // Aceitou
				
				// relaciona a pessoa com a partida
				relaciona_jugador(conn, nombre, idbdgames);
				
				// Adiciona uma pessoa a mais no dono e se completou avisa o dono
				// So vai entrar em jogo ate ficar completo
				usuario->jugadores_momento+=1;
				// Confere se completou as pessoas
				
				if(usuario->jugadores_momento == usuario->jugadores_partida){
					
					printf("Todos ja estao prontos para comecar\n"); 
				}else{
					
					printf("Ainda faltam pessoas\n"); 
				}
				
				
				// Pode fazer para avisar que entrou na partida tambem
				// Insere e avisa o dono que entrou
				//write(getsocket(*lista,convidado),conviteres, strlen(conviteres));
				
				
			}else{ // Recusou				
				
				// Se recusou envia para todos que estao na partida que nao aceitou e deleta da base
				
			}
			
			
			
			
			// Vai verificar se aceitou ou nao e alterar a quantidade de conectados
			
			// Caso se a pessoa aceitou depois que nao existe mais, para isso vai verificar se existe na BASE
			// de dados uma prtida com o id, se nao existe avisa que nao existe mais, se existe
			// altera o dono da partida e verifica se esta cheio e envia para ele que pode comecar
			
			
			// Ya tenemos el nombre
			
			// Cria partida insere quem convidou e faz loop com os outros
			// Cria partida e devolve id
			// Ate aqui ja tenho quem criou o jogo
			// Agora relaciono o criador do jogo

			// A cada resposta altera osvalores de quem criou a partida
			
			
			// Se alguem nao aceita deleta tudo relacionado ao jogo
			
			
			// Aqui avisa que entrou na partida
			sprintf(respuesta,"7/1%s",nombre);
		}
		
		if(codigo !=0){ // Desconectar
			printf ("Resposta: %s\n", respuesta);
			// Enviamos a resposta
			
			write(suser,respuesta, strlen(respuesta));
			
		}if ((codigo == 0)||(codigo == 1)||(codigo== 2)||(codigo== 3)||(codigo== 5)||(codigo== 6)){
			
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
