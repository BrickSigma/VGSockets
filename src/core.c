#if defined _WIN32 || defined __CYGWIN__
    #include <winsock2.h>
#else
    #include <arpa/inet.h>
    #include <sys/socket.h>
    #include <unistd.h>
#endif

#include <string.h>

#include "vgs.h"

int InitVGS(void)
{
#if defined _WIN32 || defined __CYGWIN__
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
#if defined _WIN32 || defined __CYGWIN__
    if (WSACleanup() != 0) {
        return STATUS_ERROR;
    }
#endif
    return STATUS_SUCCESS;
}

Socket StartupServer(int type, int port, int backlog)
{
    Socket fd = socket(AF_INET, type, 0);
    struct sockaddr_in server;
    memset(&server, 0, sizeof(server));

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

    if (type == TCP) {
        if (listen(fd , backlog) < 0) {
            ShowError("ERROR LISTENING FOR CONNECTIONS");
            return STATUS_ERROR;
        }
    }

    return fd;
}

Socket AcceptClient(Socket fd)
{
#if defined _WIN32 || defined __CYGWIN__
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

Socket StartupClient(int type, Sockaddr address)
{
    Socket fd = socket(AF_INET, type, 0);

    if (fd == INVALID_SOCKET) {
        ShowError("ERROR CREATING SERVER SOCKET");
		return INVALID_SOCKET;
	}

    struct sockaddr_in server;
    memset(&server, 0, sizeof(server));

    // Server address details
    server.sin_addr.s_addr = address.addr;
    server.sin_family = AF_INET;
    server.sin_port = address.port;

    //Connect to remote server
    if (connect(fd , (struct sockaddr *)&server , sizeof(server)) != 0)
    {
        ShowError("ERROR CONNECTING SERVER");
        return STATUS_ERROR;
    }

    return fd;
}

unsigned int IpAddr(const char *address) {
    return inet_addr(address);
}

Sockaddr LoadAddr(int port, const char *address) {
    Sockaddr addr;
    addr.port = htons(port);
    addr.addr = inet_addr(address);

    return addr;
}

int CloseSocket(Socket fd)
{
#if defined _WIN32 || defined __CYGWIN__
    if (closesocket(fd) != 0) {
        ShowError("ERROR CLOSING SOCKET");
        return STATUS_ERROR;
    }
#else
    if(close(fd) != 0) {
        ShowError("ERROR CLOSING SOCKET");
        return STATUS_ERROR;
    }
#endif

    return STATUS_SUCCESS;
}

int SendData(Socket fd, const void *buf, int len)
{
    int valsent = send(fd, buf, len, 0);
    if (valsent < 0) {
        ShowError("ERROR SENDING");
        return STATUS_ERROR;
    }

    return valsent;
}

int SendTo(Socket fd, const void *buf, int len, Sockaddr address) {
    struct sockaddr_in dst_addr;  // destination socket address
    memset(&dst_addr, 0, sizeof(dst_addr));

    dst_addr.sin_family = AF_INET;
    dst_addr.sin_addr.s_addr = address.addr;
    dst_addr.sin_port = address.port;

    int valsent = sendto(fd, buf, len, 0, (struct sockaddr *)&dst_addr, sizeof(dst_addr));
    if (valsent < 0) {
        ShowError("ERROR SENDING");
        return STATUS_ERROR;
    }

    return valsent;
}

int RecvData(Socket fd, void *buf, int len)
{
    int valrecv = recv(fd, buf, len, 0);
    if (valrecv < 0) {
        ShowError("ERROR RECEIVING");
        return STATUS_ERROR;
    }

    return valrecv;
}

int RecvFrom(Socket fd, void *buf, int len, Sockaddr *address) {
    struct sockaddr_in src_addr;  // source socket address of incoming packets
    memset(&src_addr, 0, sizeof(src_addr));
    int addrlen = sizeof(src_addr);

    int valrecv = recvfrom(fd, buf, len, 0, (struct sockaddr *)&src_addr, &addrlen);
    if (valrecv < 0) {
        ShowError("ERROR RECEIVING");
        return STATUS_ERROR;
    }

    // Update the source's address details
    address->port = src_addr.sin_port;
    address->addr = src_addr.sin_addr.s_addr;
    
    return valrecv;
}
