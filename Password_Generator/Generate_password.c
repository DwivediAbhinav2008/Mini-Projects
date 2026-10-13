#define _GNU_SOURCE
#include "wipememory.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <stddef.h>

int GeneratePassword(const size_t length)
{
    int fd = -1;
    unsigned char *password_buf = NULL;

    password_buf = calloc(length + 1, 1);
    if (!password_buf) {
        perror("calloc");
        goto cleanup;
    }

    fd = open("/dev/urandom", O_RDONLY | O_CLOEXEC);
    if (fd < 0) {
        perror("open");
        goto cleanup;
    }

    size_t i = 0;
    while (i < length) {
        unsigned char byte;
        ssize_t ret;

        do {
            errno = 0;
            ret = read(fd, &byte, 1);
        } while (ret == -1 && errno == EINTR);

        if (ret != 1)
            goto cleanup;

        /* rejection sampling to avoid modulo bias */
        if (byte >= 188)
            continue;

        password_buf[i++] = (byte % 94) + 33;
    }

    password_buf[length] = '\0';
    printf("%s\n", password_buf);

    secure_bzero(password_buf, length + 1);
    free(password_buf);
    close(fd);
    return 0;

cleanup:
    if (fd >= 0)
        close(fd);
    if (password_buf) {
        secure_bzero(password_buf, length + 1);
        free(password_buf);
    }
    return 1;
}
