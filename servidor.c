#include "servidor.h"


void *AtenderCliente (void *args_void)
{
	
	struct thread_args *args = args_void;
	int sock_conn;
	int * s;
	
	printf("Numero = %lf\n", args->b);
	
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
			strcpy (senha, p);
			
			situacao=loga_user(nombre,senha,conn);
			if (situacao == 1){
				logado=1;
				sprintf (respuesta, "1%s",nombre); // Login correto
			}else if (situacao == 3){
				sprintf (respuesta, "2%s",nombre); // Credenciais errados
			}else{
				sprintf (respuesta, "3%s",nombre); // Erro ao logar
			}
			
		}else if (codigo==5){ // insere USUARIO
			
			char senha[20];
			p = strtok( NULL, "/");
			strcpy(senha, p);
			int i = 0;
			
			//char string[]= "teste";
			
			unsigned char *result;
			
			
			result=smd5(senha);
			
			for(i = 0; i < MD5_DIGEST_LENGTH; i++){
				printf("%02x", result[i]);
			}
			
			situacao=insere_user(nombre,result,conn);
			
			if(situacao == 1){
				sprintf(respuesta,"1%s",nombre); // Inserido correto
			}else if(situacao == 2){
				sprintf(respuesta,"2%s",nombre); // Usuario ja existe
			}else{
				sprintf(respuesta,"3%s",nombre); // Erro ao inserir
			}
			
			
			free(result);
			
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
