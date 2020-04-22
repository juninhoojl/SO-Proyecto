#ifndef _FMD5_H_
#define _FMD5_H_

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <openssl/md5.h>

// Imprime MD5 em array forncido 
char * smd5(char * palavra, char * digest);

// Converte unsigned char array em char array
void fconv(char *dst,unsigned char *src,size_t src_len);

#endif
