#ifdef _WIN32
    #include <WinSock2.h>
#else
    #include <sys/socket.h>
#endif

#include "vgs.h"

typedef unsigned int u_int;

void InitVGSocket(VGSocket *vgs)
{
    if (vgs->fd_count != 0) {
        return;
    }
    vgs->fd_count = 1;
    vgs->fd_array[0] = vgs->fd;
}

void ClearSet(Socket fd, VGSocket *vgs)
{
    do { 
        u_int __i; 
        for(__i = 0; __i < vgs->fd_count; __i++) { 
            if (vgs->fd_array[__i] == fd) { 
                while (__i < vgs->fd_count - 1) { 
                    vgs->fd_array[__i] = vgs->fd_array[__i + 1]; 
                    __i++; 
                }
                vgs->fd_count--; 
                break; 
            } 
        } 
    } while(0);
}

int IsSet(Socket fd, VGSocket *vgs)
{
    fd_set readfds;
}