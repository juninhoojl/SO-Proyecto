#include "fmd5.h"

char *string = "teste";


int main0(){
	
	int i=0;
	
	unsigned char *result=smd5();
	

	if(result){
		
		for(i = 0; i < MD5_DIGEST_LENGTH; i++){
			printf("%02x", result[i]);
		}
		
		// Libera espaco 
		free(result);
	}
	
	
	
	return 1;
}

	
unsigned char * smd5(){
	
	int i;
	
	unsigned char * resultado  = malloc(sizeof(unsigned char)*MD5_DIGEST_LENGTH);
	
	//unsigned char result[MD5_DIGEST_LENGTH];
	
	MD5(string, strlen(string), resultado);
	
	for(i = 0; i < MD5_DIGEST_LENGTH; i++){
		printf("%02x", resultado[i]);
	}
	
	printf("\n");
	
	return resultado;
}
	
	

	

	
	
