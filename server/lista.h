#ifndef _LISTA_H_
#define _LISTA_H_
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXNOME 25
#define MAXELE 10
#define SEPARADOR 1

typedef struct Node {
	int socket;
	char username[MAXNOME];
	struct Node* ante;
	struct Node* prox;
	unsigned int partida;
	int jugadores_partida;
	int jugadores_momento;
	int emjogo;

}node;


int maina();

void insere(node ** cabeca, int socket, char name[MAXNOME], int * tam);

void mostra(struct Node * no);

node * busca(struct Node * no, char name[MAXNOME]);

int getsocket(struct Node * no, char name[MAXNOME]);

void elimina(node ** cabeca, char name[MAXNOME],int * tam);

void conectados(struct Node * no, char lconectados[],int * tam);

void listasockets(struct Node * no, char lconectados[], char lsockets[], int qtd);

int * vetorSocket(struct Node * no, int * tam);

#endif
