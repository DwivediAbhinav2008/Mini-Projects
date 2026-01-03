#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>
#include <stdio.h>
#define FILE_PATH "/sys/power/state"
#define SUSPEND_MODE "mem"
int main(void)
{
    char buffer[1024] = {0};
    int fd;
    ssize_t bytes_r_or_w = 0;
    /* First phase*/
    if (geteuid() != 0)
    {
        fprintf(stderr, "This program must be run as root\n");
        return 3;
    }

    fd = open(FILE_PATH, O_RDONLY);
    if (fd < 0)
    {
        fprintf(stderr, "Error %s\n", strerror(errno));
        return 1;
    }
    bytes_r_or_w = read(fd, buffer, sizeof(buffer) - 1);
    if (bytes_r_or_w <= 0)
    {
        fprintf(stderr, "\nError occured\n");
        close(fd);
        return 1;
    }

    buffer[bytes_r_or_w] = '\0';
    if (strstr(buffer, SUSPEND_MODE) == NULL)
    {
        fprintf(stderr, "Unsupported operation\n");
        close(fd);
        return 1;
    }
    close(fd);
    /*Second phase*/
    fd = open(FILE_PATH, O_WRONLY);
    if (fd < 0)
    {
        fprintf(stderr, "Error %s\n", strerror(errno));
        return 1;
    }
    bytes_r_or_w = write(fd, SUSPEND_MODE, strlen(SUSPEND_MODE));
    fsync(fd);
    if (bytes_r_or_w != strlen(SUSPEND_MODE))
    {
        fprintf(stderr, "\nError occured");
        close(fd);
        return 1;
    }
    printf("\n%s\n", "System resumed");
    close(fd);
    return 0;
}
