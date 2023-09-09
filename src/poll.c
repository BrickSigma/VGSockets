#if defined _WIN32 || defined __CYGWIN__
    #include <winsock2.h>
#else
    #include <sys/socket.h>
    #include <poll.h>
#endif

#include "vgs.h"

int Poll(Pollfd *fds, unsigned long nfds, int timeout) {
    return poll((struct pollfd *)fds, (nfds_t)nfds, timeout);
}

int TimedRecv(Socket fd, void *buf, int len, int timeout)
{
    struct pollfd pfd = {.fd = fd, .events=POLLIN};
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