#include "lista.h"

int tam=0;

void insere(head * cabeca, int socket, char name[MAXNOME]){
	
	printf("Tamanho = %d\n",cabeca->taman);
	
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
	
	//novo->prox = (*cabeca);
	novo->prox = *cabeca->plista;

	novo->ante = NULL;
	
	
	
	// Muda o anterior do no principal
	
/*	if ((*cabeca) != NULL){*/
/*		(*cabeca)->ante = novo;*/
/*	}*/
	
	if ((*cabeca->plista) != NULL){
		(*cabeca->plista)->ante = novo;
	}
	
	
	// Move a cabeca para o novo
	
/*	(*cabeca) = novo;*/
	(*cabeca->plista) = novo; 
	
	novo->prox = *cabeca->plista;
	
	cabeca->taman++;
/*	tam++;*/
}
	
	// Mostra o conteudo dos nos
void mostra(head * cabeca){
	
	// Seria o ** ja
	
	// Ja eh o valor do plista que eh um ponteiro
	printf("Ponteiro = %p\n",cabeca->plista);
	
	if (!(cabeca)->plista){
		printf("Lista vazia\n");
		return;
	}
	
	/*	if (!no){*/
	/*		printf("Lista vazia\n");*/
	/*		return;*/
	/*	}*/
	
	
	//node ** teste = (cabeca)->plista;
	//printf(" Valor = %d",(*(cabeca)->plista)->socket);
	//printf(" Nome = %s",(*(cabeca)->plista)->username);
	
	printf("%s -> %d\n",(*(cabeca)->plista)->username,(*(cabeca)->plista)->socket);
	
	
	
/*	while (no != NULL){*/
/*		printf("%s -> %d\n", no->username, no->socket);*/
/*		no = no->prox;*/
/*	}*/

/*	while (no != NULL){*/
/*		printf("%s -> %d\n", no->username, no->socket);*/
/*		no = no->prox;*/
/*	}*/

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
	
int main(){
	
	// Inicia lista
	node * cabeca = NULL;
	node * test = NULL;
	
	head cablista;
	cablista.plista=&cabeca;
	cablista.taman=220;
	
	printf("Tamanho=%d\n",cablista.taman);
	node ** teste = cablista.plista;
	insere(&cablista, 50, "Juninho");
	
	printf("Tamanho=%d\n",cablista.taman);
	
	mostra(&cablista);
	return 0;
	
/*	insere(&cabeca, 1, "jose");*/
/*	insere(&cabeca, 2, "luiz");*/
/*	insere(&cabeca, 3, "correa");*/
	
	
/*	printf("\n#########################\n");*/
/*	printf("Depois de inserir\n");*/
/*	mostra(cabeca);*/
	
/*	mostra(*teste);*/

/*	printf("\n#########################\n");*/
/*	printf("Buscando usuario\n");*/
/*	test=busca(cabeca,"jose");*/
	
/*	if(test != NULL){*/
/*		printf("\nUser %s -> Socket: %d\n", test->username, test->socket);*/
/*	}else{*/
/*		printf("Nao encontrado\n");*/
/*	}*/
	
/*	printf("\n#########################\n");*/
/*	printf("String conectados\n");*/
/*	char * novo = (char *)malloc(MAXNOME*MAXELE*sizeof(char)+SEPARADOR*sizeof(char));*/
/*	conectados(cabeca, novo);*/
/*	printf("\n%s\n",novo);*/
/*	free(novo);*/
	
	
/*	printf("\n#########################\n");*/
/*	printf("String sockets\n");*/
	
/*	char nome_cliente[] =  "correa,jose";*/
	// Numeros de ate 2 digitos
/*	char * lista_sockets = (char *)malloc(2*MAXELE*sizeof(char)+SEPARADOR*sizeof(char));*/
	
/*	listasockets(cabeca, nome_cliente, lista_sockets, 2);*/
	
/*	printf("\n%s\n",lista_sockets);*/
/*	free(lista_sockets);*/
	
/*	printf("\n#########################\n");*/
/*	printf("Buscando socket\n");*/
/*	printf("Socket = %d\n",getsocket(cabeca, "juninheo"));*/
	
/*	printf("\n#########################\n");*/
/*	printf("Removendo\n");*/
/*	elimina(&cabeca, "luiz");*/
/*	mostra(cabeca);*/
	
/*	printf("\n\n\n");*/
/*	return 0;*/
}
	
