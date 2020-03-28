#ifndef smd5_h
#define smd5_h

#include <stdio.h>
#include <mysql.h>
#include <string.h>
//#include <unistd.h>
//#include <stdlib.h>

#include <openssl/md5.h>

unsigned char * gmd5(char palavra[]);


#endif
