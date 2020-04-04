#ifndef _SERVIDOR_H_
#define _SERVIDOR_H_

#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <pthread.h>
#include "basedados.h"


struct thread_args
{
	int a;
	double b;
};

void *AtenderCliente (void *args_void);




#endif


