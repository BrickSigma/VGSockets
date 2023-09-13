#if defined _WIN32 || defined __CYGWIN__
    #include <winsock2.h>
#else
    #include <sys/socket.h>
    #include <poll.h>
#endif

#include "vgs.h"

#include <stdlib.h>


int Poll(Pollfd *fds, unsigned long nfds, int timeout) {
    struct pollfd *pfds = calloc(nfds, sizeof(struct pollfd));
    for (unsigned long i = 0; i < nfds; i++) {
        pfds[i].fd = fds[i].fd;
        pfds[i].events = fds[i].events;
    }

    int retvalue;
#if defined _WIN32 || defined __CYGWIN__
    retvalue =  WSAPoll(pfds, (unsigned long)nfds, timeout);
#else
    retvalue = poll(pfds, (nfds_t)nfds, timeout);
#endif

    free(pfds);

    return retvalue;
}

int TimedRecv(Socket fd, void *buf, int len, int timeout)
{
    struct pollfd pfd = {.fd = fd, .events = POLLIN};
    int valrecv = 0;
    int pollval = poll(&pfd, 1, timeout);
    if (pollval > 0 && (pfd.revents & POLLIN)) {
        valrecv = recv(fd, buf, len, 0);
        if (valrecv < 0) {
            ShowError("ERROR RECEIVING");
        }
    } else if (pollval < 0) {
        ShowError("ERROR POLLING FILE DESCRIPTOR");
    }

    return valrecv;
}

int TimedRecvFrom(Socket fd, void *buf, int len, Sockaddr *address, int timeout)
{
    struct pollfd pfd = {.fd = fd, .events = POLLIN};
    int valrecv = 0;
    int pollval = poll(&pfd, 1, timeout);
    if (pollval > 0 && (pfd.revents & POLLIN)) {
        valrecv = RecvFrom(fd, buf, len, address);
        if (valrecv < 0) {
            ShowError("ERROR RECEIVING");
        }
    } else if (pollval < 0) {
        ShowError("ERROR POLLING FILE DESCRIPTOR");
    }

    return valrecv;
}