#ifndef _FUNCS_
#define _FUNCS_
#define _GNU_SOURCE
#include <sys/socket.h>
#include <unistd.h> 
#include <netinet/in.h>
#include <stdio.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <dlfcn.h>
#include <time.h>
typedef int (*open_)(const char *, int, ...);
typedef int (*socket_)(int, int, int);
typedef int (*execv_)(const char *, char *const[]);
typedef int (*connect_)(int , const struct sockaddr* , socklen_t);


typedef struct Ghost_funcs
{
    open_ open_func;
    socket_ socket_func;
    execv_ execv_func;
    connect_ connect_func;
} ghost;

#endif
