#include "servidor.h"


void *AtenderCliente (void *args_void)
{
	
	struct thread_args *args = args_void;
	int sock_conn;
	int * s;
	
	printf("Numero = %lf\n", args->b);
	
	int i = 0; // laco mostra digest
	
	//s = (int*) args->a;
	sock_conn = args->a;
	
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
	
	conn=mysql_real_connect(conn,SERVIDOR,USUARIO,SENHA,BASE,0, NULL, 0);
	
	if(conn==NULL){
		printf("Erro ao iniciar conexao: %u%s\n",mysql_errno(conn),mysql_error(conn));
		exit (1);
	}
	
	
	// Entramos en un bucle para atender todas las peticiones de este cliente
	//hasta que se desconecte
	
	// So vai reatribuir senha se fizer logout ideia
	
	
	
	
	while (terminar ==0)
	{
		
		// Ahora recibimos la petici?n
		ret=read(sock_conn,peticion, sizeof(peticion));
		printf ("Recibido\n");
		
		// Tenemos que a?adirle la marca de fin de string 
		// para que no escriba lo que hay despues en el buffer
		peticion[ret]='\0';
		
		
		printf ("Peticion: %s\n",peticion);
		
		// vamos a ver que quieren
		char *p = strtok( peticion, "/");
		int codigo =  atoi (p);
		// Ya tenemos el c?digo de la petici?n
		char nombre[20];
		
		if (codigo !=0)
		{
			p = strtok( NULL, "/");
			strcpy (nombre, p);
			// Ya tenemos el nombre
			printf ("Codigo: %d, Nome: %s\n", codigo, nombre);
		}
		
		if(codigo ==0){ // Solicita sair
			
			logado=0;
			terminar=1;
			
		}else if (codigo==1){ // Solicita login
			
			printf("SOlicitou login");
			char senha[20];
			p = strtok( NULL, "/");
			int situacao=0;
			strcpy(senha, p);
			
			char *asenha = malloc((MD5_DIGEST_LENGTH*2+1)*sizeof( char));
			
			asenha = smd5(senha,asenha);
			
			printf("%s\n",asenha);
			
			situacao=loga_user(nombre,asenha,conn);
			
			if (situacao == 1){
				logado=1;
				sprintf (respuesta, "1%s",nombre); // Login correto
			}else if (situacao == 3){
				sprintf (respuesta, "2%s",nombre); // Credenciais errados
			}else if (situacao == 0){
				sprintf (respuesta, "0%s",nombre); // Erro ao logar
			}else{
				
				sprintf (respuesta, "3%s",nombre); // Erro ao logar
			}
			
			free(asenha);
			
		}else if(codigo==2){ // Solicita deslogar
			printf("SOlicitou deslogar");
			char senha[20];
			p = strtok( NULL, "/");
			int situacao=0;
			strcpy(senha, p);
			
			logado=0;
			sprintf(respuesta, "0%s",nombre); // Login correto
			
		}else if (codigo==5){ // insere USUARIO
			
			char senha[20];
			p = strtok( NULL, "/");
			strcpy(senha, p);
			
			char *hsenha = malloc((MD5_DIGEST_LENGTH*2+1)*sizeof( char));
			
			hsenha = smd5(senha,hsenha);
			
			printf("%s\n",hsenha);
			
			
			situacao=insere_user(nombre,hsenha,conn);
			
			if(situacao == 1){
				sprintf(respuesta,"1%s",nombre); // Inserido correto
			}else if(situacao == 2){
				sprintf(respuesta,"2%s",nombre); // Usuario ja existe
			}else{
				sprintf(respuesta,"3%s",nombre); // Erro ao inserir
			}
			
			
			free(hsenha);
			
		}
		
		if(codigo !=0){ // Desconectar
			printf ("Resposta: %s\n", respuesta);
			// Enviamos a resposta
			write (sock_conn,respuesta, strlen(respuesta));
		}
	}
	// Se acabo el servicio para este cliente
	close(sock_conn); 
	mysql_close (conn);
	
}
