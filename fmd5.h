#ifndef _FMD5_H_
#define _FMD5_H_


#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <openssl/md5.h>


char * smd5(char * palavra, char * digest);

int maina();



#endif
