 #include "fmd5.h"

// Retorna um ponteiro para uma string de unsigned char
// Lembrar de desalocar depois de usar
int main(){


	char *result = malloc((MD5_DIGEST_LENGTH*2+1)*sizeof( char));
	
	result = smd5("asdfghjk",result);

	printf("%s\n",result);
	
	free(result);

	return 0;
}

void fconv(char *dst,unsigned char *src,size_t src_len){
	while (src_len--) 
		dst += sprintf(dst,"%02x",*src++);
	*dst = '\0';
}


char * smd5(char * palavra, char * digest){
	
	unsigned char *result;
	result = malloc(sizeof(unsigned char)*MD5_DIGEST_LENGTH);
	MD5(palavra, strlen(palavra), result);
	fconv(digest,result,2*sizeof(result));
	free(result);
	return digest;
}


