#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
//#include <mysql.h>

#include "basedados.h"
#include "servidor.h"
#include "fmd5.h"

// /media/psf/Home/Documents/SO-Proyecto/GAME

// Para compilar terminal
// gcc main.c -std=c99 `mysql_config --cflags --libs` -lm fmd5.c basedados.c servidor.c  -lcrypto -o main.bin

// Para compilar Zinjal (em main.c Run-> COnfigure -> Extra arguments for compiler:
// -std=c99 `mysql_config --cflags --libs` -lm fmd5.c basedados.c servidor.c -lcrypto

int logado = 0;

int main(int argc, char *argv[]){
	
	//maina(); // Testando md5
	
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
	
	
	int i;
	int sockets[100];
	pthread_t thread;
	i=0;

	
	struct thread_args in;
	in.b=10;
	
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
