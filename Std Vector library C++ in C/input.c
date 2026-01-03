#include "input.h"

void read_int(const char *prompt, int *out)
{
    char buffer[30];
    char *non_charac;
    long int obt_value;
    size_t size_of_buffer = 0;
    fputs(prompt, stdout);
    if (fgets(buffer, 30, stdin) != NULL)
    {
        size_of_buffer = strlen(buffer);
        if(buffer[size_of_buffer-1] == '\n')
        buffer[size_of_buffer-1] = '\0';
        else
        flush_input();

        errno = 0;
        obt_value = strtol(buffer, &non_charac, 10);
        if (errno == ERANGE)
        {
            perror("\nError! too long or too short value ");
        }

        else if (non_charac == buffer && obt_value == 0)
        {
            errno = EINVAL;
            perror("\nError no integer supplied ");
        }
        else
        {
            *out = obt_value;
        }
    }
    else
    {
        errno = EIO;
        perror("\nError can't read input ");
    }
}
