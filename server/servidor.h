#ifndef _SERVIDOR_H_
#define _SERVIDOR_H_
#include "basedados.h"
#include "dlinkedlist.h"
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <pthread.h>
#include "dlinkedlist.h"

struct thread_args{
	int a;
	hnode * lista;
	
};

typedef struct Carta {
	int numero; // 1 2 3 4 5 6 7 8 9 10 11 12 13 (A 1 .. 10 J Q K)
	char naipe; // C D H S
}carta;


char * scartas(carta * baralho);
	
void embaralhar(carta *vet, int vetSize);

void *AtenderCliente (void *args_void);

void mostra(carta * baralho);

void preenche(carta * baralho);

#endif


