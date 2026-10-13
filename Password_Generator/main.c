#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <stddef.h>
extern int GeneratePassword(const size_t);
int main(int argc , char **argv)
{
    if(argc != 2)
    {
        printf("Usage: %s <length of password>\n" , argv[0]);
        return 1;
    }
    char *noncharac = NULL;
    errno = 0;
    long length = strtol(argv[1] , &noncharac , 10);
    if(length == 0 && (noncharac == argv[1]))
    {
        fprintf(stderr , "No value detected!\n");
        return 1;
    }
    if(length <=0 || length > 100)
    {

        fprintf(stderr , "Max length 100\n");
        return 1;
    }
    return GeneratePassword((size_t)length);
}
