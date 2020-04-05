 #include "fmd5.h"

int maina() {

	unsigned char x = 0xFF;
	unsigned char *p = &x;
	
	printf("Signed value - %d\n", *((char *)p));
	printf("Unsigned value - %u\n", *p);
	
	
	return 0;
}




// Retorna um ponteiro para uma string de unsigned char
// Lembrar de desalocar depois de usar
int main(){
	

	//result = malloc(sizeof(unsigned char)*MD5_DIGEST_LENGTH);
	//unsigned char result[MD5_DIGEST_LENGTH];
	
	
	int i=0;
	
	char string[]= "asdfghjk";
	
	//char *result;

	//char * result[MD5_DIGEST_LENGTH*2+1];
	
	char *result;
	result = malloc((MD5_DIGEST_LENGTH*2+1)*sizeof( char));
	
	
	result=smd5(string,result);

	printf("The string is: \"%s\"\n",result);
	
	//free(result);

	return 1;
}

void f(char *dst,unsigned char *src,size_t src_len)
{
	while (src_len--) 
		dst += sprintf(dst,"%02x",*src++);
	*dst = '\0';
}

int mainfa(){
	unsigned char btemp[]= { 0x04, 0x0a, 0xd0, 0xc2,0x34,0x3c,0xed,0x06,0x10,0x11};
	char representation[sizeof(btemp)*2+1];
	
	f(representation,btemp,sizeof(btemp));    
	printf("The string is: \"%s\"\n",representation);
}


char * smd5(char * palavra, char * digest){

	int i=0;
	
	unsigned char *result;
	result = malloc(sizeof(unsigned char)*MD5_DIGEST_LENGTH);
	

	//unsigned char result[MD5_DIGEST_LENGTH];
	
	// 128 bits porem em texto normal 32 bits (256)
	
	MD5(palavra, strlen(palavra), result);
	printf("tamanho md5 = %d\n",MD5_DIGEST_LENGTH);
	//char representation[sizeof(MD5_DIGEST_LENGTH)*2+1];
	
	//char normal[MD5_DIGEST_LENGTH*2+1];
	
	f(digest,result,2*sizeof(result));
	printf("The string is: \"%s\"\n",digest);
	
	for(i = 0; i < MD5_DIGEST_LENGTH; i++){
		printf("%02x", result[i]);
	}
	
	
	printf("\n");
	
	return digest;
}


