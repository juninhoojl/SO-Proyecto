#include "fmd5.h"

char *string = "teste";

unsigned char * smd5();


int main(){
	
	int i=0;
	
	unsigned char *result;
	//result = malloc(sizeof(unsigned char)*MD5_DIGEST_LENGTH);
	//unsigned char result[MD5_DIGEST_LENGTH];
	
	result=smd5();

	for(i = 0; i < MD5_DIGEST_LENGTH; i++){
		printf("%02x", result[i]);
	}


	
	return 1;
}


unsigned char * smd5(){

	
	int i;
	
	unsigned char *result;
	result = malloc(sizeof(unsigned char)*MD5_DIGEST_LENGTH);
	//unsigned char result[MD5_DIGEST_LENGTH];
	
	MD5(string, strlen(string), result);
	
	for(i = 0; i < MD5_DIGEST_LENGTH; i++){
		printf("%02x", result[i]);
	}
	
	printf("\n");
	
	return result;
}
	
 
	
