#include "lista.h"

int tam=0;

void insere(node ** cabeca, int socket, char name[MAXNOME]){
	
	if(tam>=MAXELE){
		printf("Tamanho maximo de %d elementos atingido!\n",MAXELE);
		return;
	}
	
	node * novo = (node *)malloc(sizeof(node));
	
	if(!novo){
		printf("Sem memoria disponivel!\n");
		exit(1);
	}
	
	novo->socket = socket;
	strcpy(novo->username, name);
	
	novo->prox = (*cabeca);
	novo->ante = NULL;
	
	// Muda o anterior do no principal
	if ((*cabeca) != NULL){
		(*cabeca)->ante = novo;
	}
	
	// Move a cabeca para o novo
	(*cabeca) = novo;
	tam++;
}
	
	// Mostra o conteudo dos nos
void mostra(struct Node * no){
	
	if (!no){
		printf("Lista vazia\n");
		return;
	}
	
	while (no != NULL){
		printf("%s -> %d\n", no->username, no->socket);
		no = no->prox;
	}

}
	
	
	
// Se retornar NULL nao encontrou
// Se retornar Endereco encontrou
node * busca(struct Node * no, char name[MAXNOME]){
	
	// Nao vazia
	if (no){
		
		while (no != NULL && strcmp(name,no->username) != 0){
			no = no->prox;
		}
		// Encontrou
		if(no != NULL){
			return no;
		}
	}
	
	return NULL;
}

	
// Se retornar zero nao encontrou
// Se retornar outro inteiro encontrou
int getsocket(struct Node * no, char name[MAXNOME]){
	
	node * nbu = NULL;
	
	nbu=busca(no,name);
	
	if(nbu != NULL){
		return nbu->socket;
	}
	
	// Nao encontrado
	return 0;
}
	
void elimina(node ** cabeca, char name[MAXNOME]){
	
	node * no;
	
	no=busca(*cabeca,name);
	
	if(no != NULL){
		
		if(*cabeca == no){
			// Tem proximo
			if(no->prox){
				(*cabeca) = no->prox;
				//no->prox->ante = no->ante;
			}else{
				(*cabeca) = NULL;
			}
		}
		
		// Se tiver no anterior
		if(no->ante){
			no->ante->prox = no->prox;
		}
		
		// Se tiver no proximo
		if(no->prox){
			no->prox->ante = no->ante;
		}
		
		free(no);
		tam--;
		
	}else{
		printf("Nao encontrado\n");
	}
}
	
void conectados(struct Node * no, char lconectados[]){
	
	if (!no){
		sprintf(lconectados, "%d/",tam);
		printf("\nLista vazia\n");
		return;
	}
	
	//Lista = "3/jose/luiz/correa"
	sprintf(lconectados, "%d",tam);
	while (no != NULL){
		// Adiciona aqui
		sprintf(lconectados, "%s/%s",lconectados,no->username);
		no = no->prox;
	}
}

void listasockets(struct Node * no, char lconectados[], char lsockets[], int qtd){
	
	char * sep;
	int i=0;
	char user[MAXNOME];
	
	sep = strtok(lconectados, ",");
	
	char str[3];
	
	for(i=0;i<qtd;i++){
		if (i!=0) {
			strcat(lsockets, ",");
		}
		strcpy(user, sep);
		sprintf(str, "%d", (getsocket(no, user)));
		strcat(lsockets, str);
		sep = strtok(NULL, ",");
	}
}
	
int maina(){
	
	// Inicia lista
	node * cabeca = NULL;
	node * test = NULL;
	
	
	insere(&cabeca, 1, "jose");
	insere(&cabeca, 2, "luiz");
	insere(&cabeca, 3, "correa");
	
	printf("\n#########################\n");
	printf("Depois de inserir\n");
	mostra(cabeca);
	
	
	printf("\n#########################\n");
	printf("Buscando usuario\n");
	test=busca(cabeca,"jose");
	
	if(test != NULL){
		printf("\nUser %s -> Socket: %d\n", test->username, test->socket);
	}else{
		printf("Nao encontrado\n");
	}
	
	printf("\n#########################\n");
	printf("String conectados\n");
	char * novo = (char *)malloc(MAXNOME*MAXELE*sizeof(char)+SEPARADOR*sizeof(char));
	conectados(cabeca, novo);
	printf("\n%s\n",novo);
	free(novo);
	
	
	printf("\n#########################\n");
	printf("String sockets\n");
	
	char nome_cliente[] =  "correa,jose";
	// Numeros de ate 2 digitos
	char * lista_sockets = (char *)malloc(2*MAXELE*sizeof(char)+SEPARADOR*sizeof(char));
	
	listasockets(cabeca, nome_cliente, lista_sockets, 2);
	
	printf("\n%s\n",lista_sockets);
	free(lista_sockets);
	
	printf("\n#########################\n");
	printf("Buscando socket\n");
	printf("Socket = %d\n",getsocket(cabeca, "juninheo"));
	
	printf("\n#########################\n");
	printf("Removendo\n");
	elimina(&cabeca, "luiz");
	mostra(cabeca);
	
	printf("\n\n\n");
	return 0;
}
	
