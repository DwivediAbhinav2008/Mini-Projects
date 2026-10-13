#include "headers.h"
#include <sys/stat.h>
void daemonize()
{
    pid_t pid = fork();
    if (pid < 0)
        exit(1);
    if (pid > 0)
        exit(0);
    
    if (setsid() < 0)
        exit(1);
    
    // Check return value of chdir to ensure process is isolated
    if (chdir("/") < 0)
        exit(1);
    
    umask(0);
    
        
}
