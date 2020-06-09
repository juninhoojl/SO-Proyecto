//
//  dlinkedlist.h
//  Doubly_Linked_List
//
//  Created by José Luiz Junior on 4/25/20.
//  Copyright © 2020 José Luiz Junior. All rights reserved.
//

#ifndef DLINKEDLIST_H_
#define DLINKEDLIST_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

#define MAXNOME 25
#define MAXELE 10
#define SEPARADOR 1

typedef struct Carta{
	int numero; // 1 2 3 4 5 6 7 8 9 10 11 12 13 repreentando de A a K
	char naipe; // 1 = Ouros, 2 = Espada, 3 = Copas, 4 = Paus
}carta;

typedef struct Node{
    int socket;
    char username[MAXNOME];
    unsigned int partida;
    int jugadores_partida;
    int jugadores_momento;
    int emjogo;
    int pontos;
    int data;//Pontos
    struct Node * next;
    struct Node * prev;
	struct Carta baralho[52];
	int poscarta;
	
}node;

typedef struct Hnode{
    int tam;
	pthread_mutex_t mutexvar;
    struct Node * first;
    struct Node * last;
	
}hnode;

// Para ordenacao


void insert_end(hnode * cabeca, node * newnode);

void remove_all(hnode * cabeca);
void remove_node(hnode * cabeca, node * nremove);
void show_list(hnode * cabeca);

void show_node(node * no);
hnode * new_list(void);
hnode * initialize_list(hnode * head);

// 1-Primeiro maior 0-Iguais 1-Segundo maior
int compare_node(node * first, node * second);
// Novo node
// Um novo jogador eh criado passando o nome e socket
node * new_node(int socket, char name[MAXNOME]);
// buca node
node * search_node(hnode * cabeca, char name[MAXNOME]);

// Para criar
void alter_pontos(hnode * cabeca, char name[MAXNOME], int valor);

void alter_idgame(hnode * cabeca, char name[MAXNOME], unsigned int valor);

void alter_emjogo(hnode * cabeca, char name[MAXNOME], int valor); //  1 sim // 2 nao

void alter_jugadores_partida(hnode * cabeca, char name[MAXNOME], int valor);

// Incrementa 1 en jugadores en la partida
void sum_jugadores_momento(hnode * cabeca, char name[MAXNOME]);
// Tira 1 en jugadores en la partida
void sub_jugadores_momento(hnode * cabeca, char name[MAXNOME]);

int get_socket(hnode * cabeca, char name[MAXNOME]);

char * get_nombre(hnode * cabeca, int socket);

int get_pontos(hnode * cabeca, char name[MAXNOME]);

unsigned int get_partida(hnode * cabeca, char name[MAXNOME]);

int get_jugadores_momento(hnode * cabeca, char name[MAXNOME]);

int * vetor_socket(hnode * cabeca); // Retorna vetor de sockets

int * vetor_socket_partida(hnode * cabeca, unsigned int idpartida);

char * string_conectados(hnode * cabeca);

char * string_conectados_partida(hnode * cabeca, unsigned int idpartida);

// Funcao que recolhe numero de conectados do momento

int qtd_conectados_partida(hnode * cabeca, unsigned int idpartida);


int qtd_conectados(hnode * cabeca);

// Funcao que retorna
// nomes concatenados com pontos
char * string_conectados_partida_pontos(hnode * cabeca, unsigned int idpartida);

char * string_conectados_indicador_jogo(hnode * cabeca);
// String com nome dos usuarios e se estao ou nao em jogo

// Reseta valores de um usuario apos sair de uma partida
void retira_partida(hnode * cabeca, char name[MAXNOME]);

#endif /* dlinkedlist_h */
