#ifdef _WIN32
    #include <WinSock2.h>
#else
    #include <sys/socket.h>
    #include <sys/time.h>
    #include <stddef.h>
#endif

#include "vgs.h"

/**
 * @brief Convert Timer type to timeval type
 * 
 * @param timeout 
 * @return struct timeval 
 */
static struct timeval TimerVal(Timer timeout);

void InitVGSocket(VGSocket *vgs)
{
    FD_ZERO((fd_set *)&(vgs->set));
    FD_SET(vgs->fd, (fd_set *)&(vgs->set));
    vgs->max_fd = vgs->fd;
}

void ClearSet(Socket fd, VGSet *set)
{
    FD_CLR(fd, (fd_set *)set);
}

int IsSet(Socket fd, VGSet *set)
{
    return FD_ISSET(fd, (fd_set *)set);
}

void AddSet(Socket fd, VGSet *set)
{
    FD_SET(fd, (fd_set *)set);
}

void ZeroSet(VGSet *set)
{
    FD_ZERO((fd_set *)set);
}

int VGSelect(int nfds, VGSet *readfds, VGSet *writefds, VGSet *exceptfds, Timer *timer)
{
    struct timeval *ptr;
    if (timer != NULL) {
        struct timeval timeout = TimerVal(*timer);
        ptr = &timeout;
    } else {
        ptr = NULL;
    }
    return select(nfds, (fd_set *)readfds, (fd_set *)writefds, (fd_set *)exceptfds, ptr);
}

int VGSRecv(VGSocket vgs, Socket fd, void *buf, int len, Timer *timer)
{
    struct timeval *ptr;
    if (timer != NULL) {
        struct timeval timeout = TimerVal(*timer);
        ptr = &timeout;
    } else {
        ptr = NULL;
    }

    int valrecv = 0;
    if (select(vgs.max_fd+1, (fd_set *)&vgs.set, NULL, NULL, ptr)) {
        if (IsSet(fd, &vgs.set)) {
            valrecv = recv(fd, (char *)buf, len, 0);
            if (valrecv <= 0) {
                ShowError("ERROR RECEIVING");
            }   
        }
    }

    return valrecv;
}

static struct timeval TimerVal(Timer timeout)
{
    return (struct timeval){.tv_sec=timeout.sec, .tv_usec=((timeout.msec*1000) + timeout.usec)};
}