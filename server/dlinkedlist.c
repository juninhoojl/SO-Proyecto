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
	newnode->isdono = 0;
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
    
	
	// tamanho/jog1/pontjog1/jog2/pontjog2...
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
	
	
	printf("Retirando DA PARTIDA -> %s\n",name);
    node * user = search_node(cabeca,name);
    user->emjogo=0;
    user->jugadores_momento=0;
    user->jugadores_partida=0;
    user->pontos=0;
    user->partida=0;
	user->isdono=0;
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

void make_dono(hnode * cabeca, char name[MAXNOME]){
	
	node * dono = search_node(cabeca, name);
	dono->isdono = 1;
	
}

void preenche(hnode * cabeca, char name[MAXNOME]){
	
	//pthread_mutex_lock(&cabeca->mutexvar);
	
	node * pessoa = search_node(cabeca,name);
	pessoa->poscarta = 0;// inicia na posicao zero e vai comparar sempre com a seguinte
	
	carta temp;
	printf("Comecou a embaralhar\n");
	// loop de 13 e poe 4 em cada
	int aux = 0;
	for (aux=0; aux<13; aux+=1){
		pessoa->baralho[aux].numero = aux+1;
		pessoa->baralho[aux].naipe = 'C';
	}
	for (aux=13; aux<26; aux+=1){
		pessoa->baralho[aux].numero = aux+1-13;
		pessoa->baralho[aux].naipe = 'D';
	}
	for (aux=26; aux<39; aux+=1){
		pessoa->baralho[aux].numero = aux+1-26;
		pessoa->baralho[aux].naipe = 'H';
	}
	for (aux=39; aux<52; aux+=1){
		pessoa->baralho[aux].numero = aux+1-39;
		pessoa->baralho[aux].naipe = 'S';
	}
	
	for (int aux = 0; aux < 52; aux++){
		int r = rand() % 52;
		temp.numero = pessoa->baralho[aux].numero;
		temp.naipe = pessoa->baralho[aux].naipe;
		pessoa->baralho[aux].numero = pessoa->baralho[r].numero;
		pessoa->baralho[aux].naipe = pessoa->baralho[r].naipe;
		pessoa->baralho[r].numero = temp.numero;
		pessoa->baralho[r].naipe = temp.naipe;
	}
	
	printf("Terminou de embaralhar\n");
	//for (aux=0; aux<52; aux++) {
	//	printf("Carta %d => %d%c\n",aux,pessoa->baralho[aux].numero,pessoa->baralho[aux].naipe);
	//}
	
	//pthread_mutex_unlock(&cabeca->mutexvar);
	
	return;
}
	

// 1 a primeira eh maior
// 0 iguais
// 2 segunda eh maior
int compara(carta seguinte, carta atual){
	
	char h = 'H', c = 'C', d = 'D', s = 'S';
	
	if (seguinte.numero > atual.numero) {
		return 1; // Primeira eh maior
		
	}else if (seguinte.numero < atual.numero){
		return 2; // Segunda eh maior
		
	}else{
		// Aqui entra a comparacao dos nipes
		if (seguinte.naipe == h) { // Maior naipe
			return 1; // Primeira eh maior
			
		}else if (seguinte.naipe == s){ // Menor naipe
			return 2; // Segunda eh maior
			
		}else if(seguinte.naipe == c && atual.naipe != h){
			return 1; // Primeira eh maior
			
		}else if(seguinte.naipe == d && atual.naipe == s){
			return 1; // Primeira ganhou
			
		}else{
			return 2; // Segunda eh maior
		}
		
		return 1; // Primeira eh maior
	}
}


int aposta(hnode * cabeca, char jogador[MAXNOME], int aposta){
	
	// 1 - acha que eh maior
	// 2 - acha que eh menor
	// Nao tem como ser igual por conta dos naipes

	// Busca dono
	
	struct Node * atual = cabeca->first;
	
	// Busca quem jogou
	node * sjogador = search_node(cabeca,jogador);

	unsigned int idpartida = sjogador->partida;
	//namedono = (char*)malloc(MAXNOME*sizeof(char));

	node * ndono = search_dono(cabeca,idpartida);

	int resaposta = compara(ndono->baralho[ndono->poscarta+1], ndono->baralho[ndono->poscarta]);
	
	ndono->poscarta+=1; // Movimenta para a seguinte ja
	
	if (resaposta == 1 && aposta == 1) { // maior
		
		sjogador->pontos+=2;
		return 1; // disse que era maior e eh maior (acertou)
		
	}else if(resaposta == 1 && aposta == 2){ // Disse que era menor e eh maior
		
		sjogador->pontos-=4;
		return 2;
		
	}else if(resaposta == 2 && aposta == 2){ // Disse que era menor e eh menor (acertou)
		
		sjogador->pontos+=2;
		return 3;
		
	}else{ // Disse que era maior e eh menor
		
		sjogador->pontos-=4;
		return  4;
		
	}
	
	/*
	A funcao que recebe o retorno dessa daqui ja deve conferir
	se a partida esta a ponto de acabar. 
	Fazer funcao para acabar partida que vai basicamente salvar na base de dados
	e mostrar o resultado para todos da partida
	
	*/
	
}
	
node * search_dono(hnode * cabeca, unsigned int idpartida){
	
	// O tamanho vai ser int (numero conectados) + tam*maxnome
	//char * namedono;
	struct Node * atual = cabeca->first;
	//namedono = (char*)malloc(MAXNOME*sizeof(char));
	
	while(atual){
		if(atual->partida == idpartida && atual->isdono == 1){ 
			
			printf("Dono da partida %u: %s\n",idpartida,atual->username);
			return atual;
		}
		atual = atual->next;
	}
	
}
	
int isultima(hnode * cabeca, char jogador[MAXNOME]){
	
	// Busca dono
	
	struct Node * atual = cabeca->first;
	
	// Busca quem jogou
	node * sjogador = search_node(cabeca,jogador);
	
	unsigned int idpartida = sjogador->partida;
	//namedono = (char*)malloc(MAXNOME*sizeof(char));
	
	node * dono = search_dono(cabeca,idpartida);
	
	// cartas de 0 ate 51 
	if(dono->poscarta == 51){
		
		return 1;
		
	}else{
		
		return 0;
	}
	
	
}

void sequencia_jogo(hnode * cabeca, char jogador[MAXNOME]){
	
	
	struct Node * atual = cabeca->first;
	
	int i=0;
	
	// Busca quem jogou
	node * sjogador = search_node(cabeca,jogador);
	
	unsigned int idpartida = sjogador->partida;
	// Encontra o dono da partida
	// coloca o vetor de pessoas ai

	int tam = qtd_conectados_partida(cabeca, idpartida);
	
	node * dono = search_dono(cabeca,idpartida);

	while(atual && tam>0){
		if(atual->partida == idpartida){
			
			// Pessoa na partida
			
			printf("PESSOA NA PARTIDA =%s\n",atual->username); 
			// strcpy(dono->sequencia[i],atual->username);
			
			dono->sequencia[i] = (char*)malloc(MAXNOME*sizeof(char));
			strcpy(dono->sequencia[i], atual->username);
			i+=1;
			tam-=1;
		}
		atual = atual->next;
	}
	
}


node * finaliza_salva(hnode * cabeca, unsigned int idpartida,MYSQL *conn){
	
	
	// Vai salvar todos os pontos e depois o vencedor
	
	//salva_jogo(MYSQL *conn, unsigned int id_game, char jugador[], int pontos);
	
	int tam = qtd_conectados_partida(cabeca, idpartida);
	int auxt = tam;
	int valorRe = 0;
	struct Node * atual = cabeca->first;
	node * vencedor;
	
	while(atual && tam>0){
		if(atual->partida == idpartida){
			
			// Se for a primeira o primeiro eh o maior
			if(tam == auxt){//primeiro loop
				vencedor = atual;
			}else{
				if(atual->pontos > vencedor->pontos){
					
					vencedor = atual;
				}
			}
			
			// Nesse mesmo loop posso conseguir o que tem mais pontos
			valorRe = salva_jogo(conn, idpartida,atual->username,atual->pontos);
			
			//sprintf(sconectados, "%s/%s/%d",sconectados,atual->username,atual->pontos);
			
			tam-=1;
		}
		atual = atual->next;
	}
	

	if(valorRe == 1){
		
		printf("Erro ao salvar os pontos\n");
	}
	// Coloca vencedor
	finaliza_jogo(conn,idpartida,vencedor->username);
	
	if(valorRe == 1){
		
		printf("Erro ao definir o vencedor\n");
	}
	
	return vencedor;
}

	
