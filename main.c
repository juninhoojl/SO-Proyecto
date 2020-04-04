#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <mysql.h>

#include "basedados.h"
#include "servidor.h"
#include "fmd5.h"

// /media/psf/Home/Documents/SO-Proyecto/GAME

// Para compilar terminal
// gcc main.c -std=c99 `mysql_config --cflags --libs` -lm fmd5.c basedados.c servidor.c  -lcrypto -o main.bin

// Para compilar Zinjal (em main.c Run-> COnfigure -> Extra arguments for compiler:
// -std=c99 `mysql_config --cflags --libs` -lm fmd5.c basedados.c servidor.c -lcrypto

int logado = 0; // 0 = nao

int main(int argc, char *argv[]){
	
	maina(); // Testando md5
	
	MYSQL *conn;
	conn=mysql_init(NULL);
	
	int sock_conn, sock_listen;
	struct sockaddr_in serv_adr;

	// Socket que vai esperar por alguma conexao, de escuta
	if ((sock_listen = socket(AF_INET, SOCK_STREAM, 0)) < 0){
		printf("Error ao criar socket");
	}
	
	memset(&serv_adr, 0, sizeof(SERVIDOR));
	serv_adr.sin_family = AF_INET;
	
	// Estamos escutando de qualquer endereco ip
	serv_adr.sin_addr.s_addr = htonl(INADDR_ANY);
	
	// Associamos o socket que criamos com porta e tipo de dados
	serv_adr.sin_port = htons(PORTA);
	
	if (bind(sock_listen, (struct sockaddr *) &serv_adr, sizeof(serv_adr)) < 0){
		printf ("Erro ao fazer bind");
		exit(1);
	}
	
	// Ate 5 podem estar na fila esperando pelo servidor
	if (listen(sock_listen, 5) < 0){
		printf("Erro na escuta");
		exit(1);
	}
	

	
	//int i;
	
	//char players[QTDMAX][TAMUSERNAME] = {"jose", "juninhoojl", "luiz"};
	
	//int qtdp = 3;
	
	//int i=0;
	
	//unsigned int id_jogo=0;
	
	
	// Ler lista de pessoas para um mesmo jogo
	// Cria jogo
	// Pega o id e adiciona na lista
	
	

	
	/*	INSERT INTO Game (Duracion,Vencedor) VALUES (33,1);*/
	/*	INSERT INTO Game (Duracion,Vencedor) VALUES (30,2);*/
	
	/*	INSERT INTO Relaciona (IDg,IDp) VALUES (1,1);*/
	/*	INSERT INTO Relaciona (IDg,IDp) VALUES (1,2);*/
	
	//int err;
	
	
	
	
	/*
	for(i=0;i<qtdp;i++){
	printf("Player %d = %s\n",i,players[i]);
	}
	
	*/
	
/*	insere_user("juninhos1","1qaz2wsx",conn);*/
	
/*	insere_user("jose","asdfghjk",conn);*/
	
/*	insere_user("hash","e7d80ffeefa212b7c5c55700e4f7193e",conn);*/
	
/*	loga_user("jose","asdfghjk",conn);*/
	
/*	desativa_user("jose","asdfghjk",conn);*/
	
/*	printf("ATIVO = %d", user_ativo("juninhos1",conn));*/
	
/*	ativa_user("jose","asdfghjk",conn);*/
	
	// Descomentar para inserir jugadores
	//insere_Player(PLAYERFILE, conn);
	
	//id_jogo=cria_Game(conn, players, qtdp);
	
	//altera_Pontuacao(conn, 1, players[0], 10);
	
	//qtdp=3;
	
	// Descomentar para criar juego
	//
	//printf("IdJogo = %u\n",id_jogo); 
	
	/*	for(i=0;i<qtdp;i++){*/
	/*		printf("Player %d = %s\n",i,players[i]);*/
	/*	}*/
	
	// Agora ja relaciona jogadores da lista usando id do game

	
	int i;
	int sockets[100];
	pthread_t thread;
	i=0;
	
	//struct thread_args in = { .a = 10, .b = 3.141592653 };
	
	struct thread_args in;
	in.b=10;
	
	
	// Laco infinito
	for (;;){
		
		//int terminar =0;
		// Atender esse cliente ate que se desconecte
		int situacao = 0;
		// COMECA AQUIIIIIIIIIIIIIIIIIIIII
		
		printf ("Escuchando\n");
		
		sock_conn = accept(sock_listen, NULL, NULL);
		printf ("He recibido conexion\n");
		
		sockets[i] =sock_conn;
		
		// passa somente um inteiro
		
		in.a=sock_conn;
		
		//sock_conn es el socket que usaremos para este cliente
		
		// Crear thead y decirle lo que tiene que hacer
		
		pthread_create (&thread, NULL, AtenderCliente,&in);
		i=i+1;
		
	}
}
