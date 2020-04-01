#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "basedados.h"
#include "servidor.h"
#include "fmd5.h"

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

// /media/psf/Home/Documents/SO-Proyecto/GAME

// Para compilar terminal
// gcc main.c -std=c99 `mysql_config --cflags --libs` -lm fmd5.c basedados.c servidor.c  -lcrypto -o main.bin
// Para compilar Zinjal (em main.c Run-> COnfigure -> Extra arguments for compiler:
// -std=c99 `mysql_config --cflags --libs` -lm fmd5.c basedados.c servidor.c -lcrypto

int logado = 0; // 0 = nao

int main(int argc, char *argv[]){
	
	maina(); // Testando md5
	
	int sock_conn, sock_listen, ret;
	struct sockaddr_in serv_adr;
	char peticion[512];
	char respuesta[512];
	
	// Socket que vai esperar por alguma conexao, de escuta
	if ((sock_listen = socket(AF_INET, SOCK_STREAM, 0)) < 0)
		printf("Error ao criar socket");
	// Fem el bind al port
	
	memset(&serv_adr, 0, sizeof(SERVIDOR));
	serv_adr.sin_family = AF_INET;
	
	// Estamos escutando de qualquer endereco ip
	serv_adr.sin_addr.s_addr = htonl(INADDR_ANY);
	// Associamos o socket que criamos com porta e tipo de dados
	serv_adr.sin_port = htons(PORTA);
	
	if (bind(sock_listen, (struct sockaddr *) &serv_adr, sizeof(serv_adr)) < 0)
		printf ("Erro ao fazer bind");
	
	// A fila de xonecoes nao pode ser maior que 3
	// Ate 3 podem estar na fila esperando pelo servidor
	if (listen(sock_listen, 3) < 0)
		printf("Erro na escuta");
	
	int i;
	
	char players[QTDMAX][TAMUSERNAME] = {"jose", "juninhoojl", "luiz"};
	
	int qtdp = 3;
	
	//int i=0;
	
	unsigned int id_jogo=0;
	
	
	// Ler lista de pessoas para um mesmo jogo
	// Cria jogo
	// Pega o id e adiciona na lista
	
	MYSQL *conn;
	int err;
	
	conn=mysql_init(NULL);
	
	/*	INSERT INTO Game (Duracion,Vencedor) VALUES (33,1);*/
	/*	INSERT INTO Game (Duracion,Vencedor) VALUES (30,2);*/
	
	/*	INSERT INTO Relaciona (IDg,IDp) VALUES (1,1);*/
	/*	INSERT INTO Relaciona (IDg,IDp) VALUES (1,2);*/
	
	
	if(conn==NULL){
		printf("Error ao criar conexao: %u %s\n",mysql_errno(conn), mysql_error(conn));
		exit (1);
	}
	
	conn=mysql_real_connect(conn,SERVIDOR,USUARIO,SENHA,BASE,0, NULL, 0);
	
	if(conn==NULL){
		printf("Erro ao iniciar conexao: %u%s\n",mysql_errno(conn),mysql_error(conn));
		exit (1);
	}
	
	
	/*
	for(i=0;i<qtdp;i++){
	printf("Player %d = %s\n",i,players[i]);
	}
	
	*/
	
	insere_user("juninhos1","1qaz2wsx",conn);
	
	insere_user("jose","asdfghjk",conn);
	
	insere_user("hash","e7d80ffeefa212b7c5c55700e4f7193e",conn);
	
	loga_user("jose","asdfghjk",conn);
	
	desativa_user("jose","asdfghjk",conn);
	
	printf("ATIVO = %d", user_ativo("juninhos1",conn));
	
	ativa_user("jose","asdfghjk",conn);
	
	// Descomentar para inserir jugadores
	//insere_Player(PLAYERFILE, conn);
	
	//id_jogo=cria_Game(conn, players, qtdp);
	
	//altera_Pontuacao(conn, 1, players[0], 10);
	
	qtdp=3;
	
	// Descomentar para criar juego
	//
	//printf("IdJogo = %u\n",id_jogo); 
	
	/*	for(i=0;i<qtdp;i++){*/
	/*		printf("Player %d = %s\n",i,players[i]);*/
	/*	}*/
	
	// Agora ja relaciona jogadores da lista usando id do game

	
	// Laco infinito
	for (;;){
		printf ("Escuchando\n");
		
		// Quando escuta algo cria um socket de conexao
		sock_conn = accept(sock_listen, NULL, NULL);

		printf ("Recebi uma conexao\n");


		int terminar =0;
		// Atender esse cliente ate que se desconecte
		int situacao = 0;
		while (terminar ==0)
		{
			// Ahora recibimos la petici?n
			ret=read(sock_conn,peticion, sizeof(peticion));
			printf ("Recibido\n");
			
			// Tenemos que a?adirle la marca de fin de string 
			// para que no escriba lo que hay despues en el buffer
			peticion[ret]='\0';
			
			
			printf ("Peticao: %s\n",peticion);
			
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
			
			if (codigo ==0){ //petici?n de desconexi?n
				terminar=1;
			}else if (codigo ==1){ //piden la longitd del nombre
				sprintf (respuesta,"%d",(int)strlen (nombre));
			}else if (codigo ==2){
				// quieren saber si el nombre es bonito
				if((nombre[0]=='M') || (nombre[0]=='S')){
					strcpy (respuesta,"SIM");
				}else{
					strcpy (respuesta,"NAO");
				}
			}else if (codigo==3){ //quiere saber si es alto
			
				p = strtok( NULL, "/");
				float altura =  atof (p);
				if (altura > 1.70){
					sprintf (respuesta, "%s eh alto",nombre);
				}else{
					sprintf (respuesta, "%s eh baixo",nombre);
				}
			}else if (codigo==4){// Busca usuario
				
				if (existe_user(nombre,conn) == 1){
					
					if(user_ativo(nombre,conn) == 1){
						sprintf (respuesta, "%s existe",nombre);
						
					}else{
						sprintf (respuesta, "%s existe (mas esta desativado)",nombre);
					}
					
				}else{
					sprintf (respuesta, "%s nao existe",nombre);
				}
				
				
			}else if (codigo==5){ // insere USUARIO
				
				char senha[20];
				p = strtok( NULL, "/");
				strcpy (senha, p);
				
				situacao=insere_user(nombre,senha,conn);
				
				if (situacao == 0){
					sprintf (respuesta, "%s inserido com sucesso",nombre);
				}else if (situacao == 1){
					sprintf (respuesta, "%s ja existe",nombre);
				}else{
					sprintf (respuesta, "%s nao pode ser inserido",nombre);
				}
				
			}else if (codigo==6){ // remove USUARIO
				
				char senha[20];
				p = strtok( NULL, "/");
				int situacao=0;
				strcpy (senha, p);
				
				situacao = desativa_user(nombre,senha,conn);
				
				if (situacao == 0){
					sprintf (respuesta, "%s desativado com sucesso",nombre);
				}else if (situacao == 2){
					sprintf (respuesta, "%s nao pode ser desativado",nombre);
				}else{
					sprintf (respuesta, "Erro ao desativar %s",nombre);
				}
				
				
			}else if (codigo==7){ // recupera USUARIO
				
				char senha[20];
				p = strtok( NULL, "/");
				int situacao=0;
				strcpy (senha, p);
				
				situacao = ativa_user(nombre,senha,conn);
				
				if (situacao == 0){
					sprintf (respuesta, "%s ativado com sucesso",nombre);
				}else if (situacao == 2){
					sprintf (respuesta, "%s nao pode ser reativado",nombre);
				}else{
					sprintf (respuesta, "Erro ao reativar %s",nombre);
				}
				
				
			}
			
			if(codigo !=0){ // Desconectar
			
				
				printf ("Resposta: %s\n", respuesta);
				// Enviamos a resposta
				write (sock_conn,respuesta, strlen(respuesta));
			}
		}
		// O servico acabou para esse cliente
		close(sock_conn); 
		mysql_close (conn);
	}
}
