#include <sys/types.h>
void d_func(unsigned char *str, unsigned char key, size_t len)
{
    for (size_t i = 0; i < len; i++)
    {
        str[i] ^= key;
    }
}
