#ifndef _SERVIDOR_H_
#define _SERVIDOR_H_

#include "basedados.h"
#include "fmd5.h"

#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <pthread.h>




struct thread_args
{
	int a;
	double b;
};

void *AtenderCliente (void *args_void);




#endif


