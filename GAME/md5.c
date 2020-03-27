#include <stdio.h>
#include <mysql.h>
#include <string.h>
//#include <unistd.h>
//#include <stdlib.h>

#include <openssl/md5.h>

char *string = "teste";

unsigned char * smd5();

int main(){
	
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
	
	

	
	
