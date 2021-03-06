#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include "dlinkedlist.h"
#include "basedados.h"
#include "servidor.h"

// #include "lista.h"
// /media/psf/Home/Documents/SO/SO-Proyecto/server

// Para compilar terminal
// gcc main.c -std=c99 `mysql_config --cflags --libs` basedados.c servidor.c dlinkedlist.c -lm -o main.bin

// Para compilar Zinjal (em main.c Run-> COnfigure -> Extra arguments for compiler:
// -std=c99 `mysql_config --cflags --libs` basedados.c servidor.c dlinkedlist.c -lm 

// Ps.: Em alguns casos Zinjal nao deleta os .bin antigos e nao compila os novos
// rm *.bin

// Visualizar o processo que esta utilizando a PORTA
// sudo fuser -v 50001/tcp
// matar ele
// kill PID


int logado = 0;

int main(int argc, char *argv[]){
	
	//maina(); // Testando lista
	MYSQL *conn;
	conn=mysql_init(NULL);
	
	int sock_listen;
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
	
	int tamanho=0;
	pthread_t thread;
	
	struct thread_args in;
	//in.b=10.0; // Numero qualquer
	
	node * cabeca = NULL;
	
	in.lista = new_list(); // Lista
	
	
	while(1){
		//int terminar =0;
		// Atender esse cliente ate que se desconecte
		int situacao = 0;
		// COMECA AQUIIIIIIIIIIIIIIIIIIIII
		printf("Escuchando\n");
		
		// passa somente um inteiro
		in.a = accept(sock_listen, NULL, NULL);
		printf("He recibido conexion\n");
		//sock_conn es el socket que usaremos para este cliente
		// Crear thead y decirle lo que tiene que hacer
		
		pthread_create(&thread, NULL, AtenderCliente, &in);
	}
	
}
