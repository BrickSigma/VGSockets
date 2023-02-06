#ifdef _WIN32
    #include <winsock2.h>
#endif

#include "vgs.h"

#include <stdio.h>
#include <errno.h>

// Used to disable/enable error messages.
int ShowErrorsMsg = 1;

void EnableErrorShow(void)
{
    ShowErrorsMsg = 1;
}

void DisableErrorShow(void)
{
    ShowErrorsMsg = 0;
}

void ShowError(const char *msg)
{
    if (ShowErrorsMsg) {
#ifdef _WIN32
        fprintf(stderr, "WIN32::%s: %d\n", msg, WSAGetLastError());
#else
        static char buff[1024];
        snprintf(buff, 1024, "UNIX::%s", msg);
        perror(buff);
#endif
    }
}