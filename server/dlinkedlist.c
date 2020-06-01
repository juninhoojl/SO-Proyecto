//
//  dlinkedlist.c
//  Doubly_Linked_List
//
//  Created by José Luiz Junior on 4/25/20.
//  Copyright © 2020 José Luiz Junior. All rights reserved.
//

#include "dlinkedlist.h"

void show_node(node * no){
    printf("-------------------------------\n");
    printf("* Player: %s\n", no->username);
    printf("\tSocket: %d\n", no->socket);
    
    // So mostra se estiver em partida
    if (no->emjogo) {// Se estiver em jogo
        printf("\tPartida: %u\n", no->partida);
        printf("\tPontos: %d\n", no->pontos);
    }else{
        printf("\tNo esta en ninguna partida!\n");
    }

    return;
}

// 1-Primeiro maior 0-Iguais 1-Segundo maior
// Usar isso para pegar o que tem maior pontuacao
int compare_node(node * first, node * second){
    
    if(first->data > second->data){
        return 1;
        
    }else if(first->data < second->data){
        return -1;
        
    }
    
    return 0; // Iguais
}

node * new_node(int socket, char name[MAXNOME]){
    
    node * newnode = (node*)malloc(sizeof(node));
	
    if(!newnode){
        printf("Memory allocation failed");
        exit(1);
    }
    
    // Vai passar o nome e o socket dele
    
    newnode->socket = socket;
    newnode->emjogo = 0;
    newnode->pontos = 0;
    strcpy(newnode->username, name);
    
    newnode->prev = NULL;
    newnode->next = NULL;
    
    return newnode;
}


void remove_all(hnode * cabeca){
    
    struct Node * atual = cabeca->first;
    struct Node * aux = NULL;
	pthread_mutex_lock(&cabeca->mutexvar);
    
    while(atual){
        aux = atual;
        atual = atual->prev;
        free(aux);
    }
    
    cabeca->first = NULL;
    cabeca->last = NULL;
    cabeca->tam = 0;
	
	pthread_mutex_unlock(&cabeca->mutexvar);
    
    return;
}

void remove_node(hnode * cabeca, node * nremove){
	
	
	if (cabeca->tam == 1){
		remove_all(cabeca);
		return;
	}
	
	pthread_mutex_lock(&cabeca->mutexvar);
	
    if(cabeca->first == nremove){ // Se primeiro
        
        cabeca->first = nremove->next;
        nremove->next->prev = NULL;
        
    }else if(cabeca->last == nremove){ // Se ultimo
        
        cabeca->last = nremove->prev;
        nremove->prev->next = NULL;
        
    }else{
        
        nremove->prev->next = nremove->next;
        nremove->next->prev = nremove->prev;
        
    }
    
    free(nremove);
    
    cabeca->tam-=1;
	pthread_mutex_unlock(&cabeca->mutexvar);
    
    return;
}


void insert_end(hnode * cabeca, node * newnode){
    
    //node * novo = new_node(valor);
    //novo->data = valor;
	
    newnode->prev = cabeca->last;
	
	pthread_mutex_lock(&cabeca->mutexvar);
    
    if (cabeca->last){
        cabeca->last->next = newnode;
    }
    
    if (!cabeca->first){
        cabeca->first = newnode;
    }
    
    cabeca->last = newnode;
    cabeca->tam+=1;
	
	pthread_mutex_unlock(&cabeca->mutexvar);
    
    return;
}


void show_list(hnode * cabeca){
    
    struct Node * atual = cabeca->first;
    
    //printf("Lista tamanho = %d\n", cabeca->tam);
    
    if (!atual) {
        printf("Lista vazia!\n");
        return;
    }
	
    while(atual){
        show_node(atual);
        //printf("%d ", atual->data);
        atual = atual->next;
    }
    
    atual = cabeca->last;
    
    return;
}


node * search_node(hnode * cabeca, char name[MAXNOME]){
    
    struct Node * atual = cabeca->first;
    
	pthread_mutex_lock(&cabeca->mutexvar);
    while(atual && strcmp(name,atual->username) != 0){
        atual = atual->next;
    }

    if(atual){
		pthread_mutex_unlock(&cabeca->mutexvar);
        return atual;
    }
	pthread_mutex_unlock(&cabeca->mutexvar);
	
    
    return NULL;
}



hnode * new_list(void){
    hnode * newlist = (hnode *)malloc(sizeof(hnode));
    initialize_list(newlist);
    return newlist;
}

hnode * initialize_list(hnode * head){
    head->first = NULL;
    head->last = NULL;
	pthread_mutex_init(&head->mutexvar,NULL);
    head->tam = 0;
    return NULL;
}

// Todas que alteram basicamente vao simplesmente fazer o intermedio
void alter_pontos(hnode * cabeca, char name[MAXNOME], int valor){
    search_node(cabeca,name)->pontos = valor;
}

void alter_idgame(hnode * cabeca, char name[MAXNOME], unsigned int valor){
    search_node(cabeca,name)->partida = valor;
}

void alter_jugadores_partida(hnode * cabeca, char name[MAXNOME], int valor){
    search_node(cabeca,name)->jugadores_partida = valor;
}

void sum_jugadores_momento(hnode * cabeca, char name[MAXNOME]){
    search_node(cabeca,name)->jugadores_momento += 1;
}

void sub_jugadores_momento(hnode * cabeca, char name[MAXNOME]){
    search_node(cabeca,name)->jugadores_momento -= 1;
}

void alter_emjogo(hnode * cabeca, char name[MAXNOME], int valor){
    
    search_node(cabeca,name)->emjogo = 1;
}


int get_socket(hnode * cabeca, char name[MAXNOME]){
    
    return search_node(cabeca,name)->socket;
}

char * get_nombre(hnode * cabeca, int socket){
	
	char * nombre = (char*)malloc((MAXNOME)*sizeof(char));
	struct Node * atual = cabeca->first;
	// busca aqui

	pthread_mutex_lock(&cabeca->mutexvar);
	
	while(atual && atual->socket!=socket){
		atual = atual->next;
	}
	
	if(atual){
		nombre = atual->username;
		pthread_mutex_unlock(&cabeca->mutexvar);
		return nombre;
	}
	
	pthread_mutex_unlock(&cabeca->mutexvar);
	
	return NULL;
}

int get_pontos(hnode * cabeca, char name[MAXNOME]){
    
    return search_node(cabeca,name)->pontos;
}

int * vetor_socket_partida(hnode * cabeca, unsigned int idpartida){
    
    int * vsockets, i = 1;
    struct Node * atual = cabeca->first;
    int tam = qtd_conectados_partida(cabeca, idpartida);
   
    vsockets = (int*)malloc((tam+1)*sizeof(int));
    
    if(!vsockets){
        printf("Sem memoria disponivel\n");
        exit(1);
    }

    vsockets[0]=tam;
	
	pthread_mutex_lock(&cabeca->mutexvar);
    
    while(atual && tam>0){
        printf("Conectado = %s -> %u\n", atual->username, atual->partida);
        if(atual->partida == idpartida){
            vsockets[i]=atual->socket;
            i+=1;
            tam-=1;
        }
        atual = atual->next;
    }
	
	pthread_mutex_unlock(&cabeca->mutexvar);
    
    return vsockets;
}

int * vetor_socket(hnode * cabeca){
    
    int * vsockets, i = 1, tam = cabeca->tam;
    struct Node * atual = cabeca->first;
   
    vsockets = (int*)malloc((tam+1)*sizeof(int));
    
    if(!vsockets){
        printf("Sem memoria disponivel\n");
        exit(1);
    }

    vsockets[0] = tam;
	
	pthread_mutex_lock(&cabeca->mutexvar);
    
    while(tam>0){
        vsockets[i] = atual->socket;
        atual = atual->next;
        i+=1;
        tam-=1;
    }

	pthread_mutex_unlock(&cabeca->mutexvar);
	
	
    return vsockets;
}

char * string_conectados(hnode * cabeca){

    // O tamanho vai ser int (numero conectados) + tam*maxnome
    int tam = cabeca->tam;
    char * sconectados;
    struct Node * atual = cabeca->first;
    
    sconectados = (char*)malloc(((tam*MAXNOME)+1)*sizeof(char));
    
    if(!sconectados){
        printf("Sem memoria disponivel\n");
        exit(1);
    }
	
    if(tam==0){
        sprintf(sconectados,"%d/",tam);
        return sconectados;
    }else{
        sprintf(sconectados,"%d",tam);
    }

	pthread_mutex_lock(&cabeca->mutexvar);
	
    while(tam>0){
        sprintf(sconectados, "%s/%s",sconectados,atual->username);
        atual = atual->next;
        tam-=1;
    }
    
	pthread_mutex_unlock(&cabeca->mutexvar);
	
    return sconectados;
}


// Arrumar isso de acordo com a quantidade de conectados da partida
char * string_conectados_partida(hnode * cabeca, unsigned int idpartida){
    
    // O tamanho vai ser int (numero conectados) + tam*maxnome
    int tam = qtd_conectados_partida(cabeca, idpartida);
    char * sconectados;
    struct Node * atual = cabeca->first;
    
    sconectados = (char*)malloc(((tam*MAXNOME)+1)*sizeof(char)+sizeof(int));
    
    if(!sconectados){
        printf("Sem memoria disponivel\n");
        exit(1);
    }
	
    if(tam==0){
        sprintf(sconectados,"%d/",tam);
        return sconectados;
    }else{
        sprintf(sconectados,"%d",tam);
    }

	
	pthread_mutex_lock(&cabeca->mutexvar);
	
    while(atual && tam>0){
        if(atual->partida == idpartida){
            sprintf(sconectados, "%s/%s",sconectados,atual->username);
            tam-=1;
        }
        atual = atual->next;
    }
    
	
	pthread_mutex_unlock(&cabeca->mutexvar);
	
    return sconectados;
}

int qtd_conectados(hnode * cabeca){
    return cabeca->tam;
}

int qtd_conectados_partida(hnode * cabeca, unsigned int idpartida){
    
    // O tamanho vai ser int (numero conectados) + tam*maxnome
    int qconectados = 0;
    struct Node * atual = cabeca->first;

    if(cabeca->tam==0){
        return 0;
    }

	pthread_mutex_lock(&cabeca->mutexvar);
	
    while(atual){
        if(atual->partida == idpartida){ // Soma 1 na quantidade
            qconectados+=1;
        }
        atual = atual->next;
    }
    
	pthread_mutex_unlock(&cabeca->mutexvar);
	
    return qconectados;
}


char * string_conectados_partida_pontos(hnode * cabeca, unsigned int idpartida){
    
	// O tamanho vai ser int (numero conectados) + tam*maxnome
	int tam = qtd_conectados_partida(cabeca, idpartida);
	char * sconectados;
	struct Node * atual = cabeca->first;

	sconectados = (char*)malloc(((tam*MAXNOME)+2)*sizeof(char)+sizeof(int));

	if(!sconectados){
	   printf("Sem memoria disponivel\n");
	   exit(1);
	}

	pthread_mutex_lock(&cabeca->mutexvar);

	if(tam==0){
	   sprintf(sconectados,"%d/",tam);
	   pthread_mutex_unlock(&cabeca->mutexvar);
	   return sconectados;
	}else{
	   sprintf(sconectados,"%d",tam);
	}
	while(atual && tam>0){
	   if(atual->partida == idpartida){
		   sprintf(sconectados, "%s/%s/%d",sconectados,atual->username,atual->pontos);
		   tam-=1;
	   }
	   atual = atual->next;
	}

	pthread_mutex_unlock(&cabeca->mutexvar);

	return sconectados;
}

char * string_conectados_indicador_jogo(hnode * cabeca){
    
    // O tamanho vai ser int (numero conectados) + tam*maxnome
    int tam = cabeca->tam;
    char * sconectados;
    struct Node * atual = cabeca->first;
    
    sconectados = (char*)malloc(((tam*MAXNOME)+2)*sizeof(char)+sizeof(int));
    
    if(!sconectados){
        printf("Sem memoria disponivel\n");
        exit(1);
    }
	
    if(tam==0){
        sprintf(sconectados,"%d/",tam);
        return sconectados;
    }else{
        sprintf(sconectados,"%d",tam);
    }
	
	pthread_mutex_lock(&cabeca->mutexvar);
	
    while(tam>0){
        sprintf(sconectados, "%s/%s/%d",sconectados,atual->username, atual->emjogo);
        atual = atual->next;
        tam-=1;
    }
	pthread_mutex_unlock(&cabeca->mutexvar);
	
    return sconectados;
}

void retira_partida(hnode * cabeca, char name[MAXNOME]){
	
    node * user = search_node(cabeca,name);
    user->emjogo=0;
    user->jugadores_momento=0;
    user->jugadores_partida=0;
    user->pontos=0;
    user->partida=0;

    // Nao esta mais em jogo, quantidades 0
    // pontos   0
    
    return;
}
	
int get_jugadores_momento(hnode * cabeca, char name[MAXNOME]){
	
	return search_node(cabeca,name)->jugadores_momento;
	
}

unsigned int get_partida(hnode * cabeca, char name[MAXNOME]){
	
	return search_node(cabeca,name)->partida;
	
}






