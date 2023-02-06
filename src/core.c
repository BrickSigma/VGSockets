#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>

#ifdef _WIN32
    #include <winsock2.h>
#else
    #include <arpa/inet.h>
    #include <sys/socket.h>
    #include <unistd.h>
    #include <sys/time.h>
#endif

#include "vgs.h"

int InitVGS(void)
{
#ifdef _WIN32
    WSADATA wsa;
    if (WSAStartup(MAKEWORD(2,0), &wsa) != 0)
	{
		return STATUS_ERROR;
	}
#endif

    return STATUS_SUCCESS;
}

int CloseVGS(void)
{
#ifdef _WIN32
    if (WSACleanup() != 0) {
        return STATUS_ERROR;
    }
#endif
    return STATUS_SUCCESS;
}

Socket StartupServer(int port, int backlog)
{
    Socket fd = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in server;

	if(fd == INVALID_SOCKET) {
        ShowError("ERROR CREATING SERVER SOCKET");
		return INVALID_SOCKET;
	}

    int opt = 1;
	if (setsockopt(fd, SOL_SOCKET,
				SO_REUSEADDR, 
				(char *)&opt, sizeof(int)) < 0) {
        ShowError("ERROR SETTING REUSEADDR");
		return STATUS_ERROR;
	}

    server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;
	server.sin_port = htons(port);

    if (bind(fd ,(struct sockaddr *)&server, sizeof(server)) < 0) {
		ShowError("ERROR BINDING SOCKET");
        return STATUS_ERROR;
	}

    if (listen(fd , backlog) < 0) {
        ShowError("ERROR LISTENING FOR CONNECTIONS");
        return STATUS_ERROR;
    }

    return fd;
}

Socket AcceptClient(Socket fd)
{
#ifdef _WIN32
    int c = sizeof(struct sockaddr_in);
#else
    socklen_t c = sizeof(struct sockaddr_in);
#endif
    Socket new_socket;
    struct sockaddr_in client;
	new_socket = accept(fd , (struct sockaddr *)&client, &c);
	if (new_socket == INVALID_SOCKET) {
        ShowError("ERROR ACCEPTING CONNECTION");
		return INVALID_SOCKET;
	}

    return new_socket;
}

Socket StartupClient(int port, char *address)
{
    Socket fd = socket(AF_INET , SOCK_STREAM , 0 );
    struct sockaddr_in server;

    if(fd == INVALID_SOCKET) {
        ShowError("ERROR CREATING SERVER SOCKET");
		return INVALID_SOCKET;
	}

    server.sin_addr.s_addr = inet_addr(address);
	server.sin_family = AF_INET;
	server.sin_port = htons(port);

	//Connect to remote server
	if (connect(fd , (struct sockaddr *)&server , sizeof(server)) != 0)
	{
        ShowError("ERROR CONNECTING SERVER");
		return STATUS_ERROR;
	}

    return fd;
}

int CloseSocket(Socket fd)
{
#ifdef _WIN32
    if (closesocket(fd) != 0) {
        ShowError("ERROR CLOSING SOCKET");
        return STATUS_ERROR;
    }
#else
    if(close(fd)) {
        ShowError("ERROR CLOSING SOCKET");
        return STATUS_ERROR;
    }
#endif

    return STATUS_SUCCESS;
}

int SendData(Socket fd, const void *buf, int len)
{
    int valsent = send(fd, (char *)buf, len, 0);
    if (valsent < 0) {
        ShowError("ERROR SENDING");
        return STATUS_ERROR;
    }
    return valsent;
}

int RecvData(Socket fd, void *buf, int len)
{
    int valrecv = recv(fd, (char *)buf, len, 0);
    if (valrecv <= 0) {
        ShowError("ERROR RECEIVING");
    }
    return valrecv;
}
