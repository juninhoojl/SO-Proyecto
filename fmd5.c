 #include "fmd5.h"

void fconv(char *dst,unsigned char *src,size_t src_len){
	while (src_len--) 
		dst += sprintf(dst,"%02x",*src++);
	*dst = '\0';
}

// Recebe a palavra e depois espaco de memoria para converter
char * smd5(char * palavra, char * digest){
	
	unsigned char *result;
	result = malloc(sizeof(unsigned char)*MD5_DIGEST_LENGTH);
	MD5(palavra, strlen(palavra), result);
	fconv(digest,result,2*sizeof(result));
	free(result);
	return digest;
	
}


