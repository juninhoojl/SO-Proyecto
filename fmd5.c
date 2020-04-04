 #include "fmd5.h"

// Retorna um ponteiro para uma string de unsigned char
// Lembrar de desalocar depois de usar
int maina(){
	

	//result = malloc(sizeof(unsigned char)*MD5_DIGEST_LENGTH);
	//unsigned char result[MD5_DIGEST_LENGTH];
	
	
	int i=0;
	
	char string[]= "teste";
	
	unsigned char *result;

	
	result=smd5(string);

	for(i = 0; i < MD5_DIGEST_LENGTH; i++){
		printf("%02x", result[i]);
	}
	
	free(result);

	return 1;
}
	

unsigned char * smd5(char * palavra){

	int i;
	
	unsigned char *result;
	result = malloc(sizeof(unsigned char)*MD5_DIGEST_LENGTH);
	//unsigned char result[MD5_DIGEST_LENGTH];
	
	MD5(palavra, strlen(palavra), result);
	
	for(i = 0; i < MD5_DIGEST_LENGTH; i++){
		printf("%02x", result[i]);
	}
	
	printf("\n");
	
	return result;
}
	
 
	
