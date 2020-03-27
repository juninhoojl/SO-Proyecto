#include "smd5.h"


char *string = "testes3";



int maino(){
	
	int i=0;
	
	unsigned char *result=gmd5(string);
	

	if(result){
		
		for(i = 0; i < MD5_DIGEST_LENGTH; i++){
			printf("%02x", result[i]);
		}
		
		// Libera espaco 
		free(result);
	}
	
	return 1;
}
	
unsigned char * gmd5(char palavra[]){
	
	int i;
	
	unsigned char * resultado  = malloc(sizeof(unsigned char)*MD5_DIGEST_LENGTH);
	
	//unsigned char result[MD5_DIGEST_LENGTH];
	
	MD5(palavra, strlen(palavra), resultado);
	
	for(i = 0; i < MD5_DIGEST_LENGTH; i++){
		printf("%02x", resultado[i]);
	}
	
	printf("\n");
	
	return resultado;
}
	
	

	
	
