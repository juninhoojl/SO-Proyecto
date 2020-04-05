 #include "fmd5.h"

// Retorna um ponteiro para uma string de unsigned char
// Lembrar de desalocar depois de usar
int main(){

	char string[]= "asdfghjk";

	char *result;
	
	result = malloc((MD5_DIGEST_LENGTH*2+1)*sizeof( char));
	
	result=smd5(string,result);

	printf("%s\n",result);
	
	free(result);

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
}


char * smd5(char * palavra, char * digest){
	
	unsigned char *result;
	result = malloc(sizeof(unsigned char)*MD5_DIGEST_LENGTH);
	MD5(palavra, strlen(palavra), result);
	f(digest,result,2*sizeof(result));
	return digest;
}


