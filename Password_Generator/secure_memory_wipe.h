#include <stddef.h>
void secure_bzero(void *ptr, size_t len)
{
    volatile unsigned char *p = ptr;
    while (len--) {
        *p++ = 0;
    }
}
