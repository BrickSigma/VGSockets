#include <stdio.h>

#include "../../src/vgs.h"

int main(void)
{
    // Enable internal error messages
    EnableErrorShow();

    printf("Initializing VGS...\n");
    InitVGS();
    
    printf("Starting up server...\n");
    Socket server = StartupServer(8080, 1);
    if (server == INVALID_SOCKET) {
        return -1;
    }
    printf("Server started!\n");
    
    printf("Waiting for client...\n");
    Socket new_socket = AcceptClient(server);
    if (new_socket == INVALID_SOCKET) {
        return -1;
    }
    printf("Client connected!\n");

    char buff[256];
    printf("Waiting for data...\n");
    int valread = RecvData(new_socket, buff, 256);
    if (valread < 0) {
        return -1;
    }
    printf("Data received: %s \nNumber of bytes received: %d\n", buff, valread);

    printf("Sending data...\n");
    int valsend = SendData(new_socket, "Hello client!", 14);
    if (valsend <= 0) {
        return -1;
    }
    printf("Successfully sent! Number of bytes sent: %d\n", valsend);

    printf("Closing server and VGS...\n");
    CloseSocket(new_socket);
    CloseSocket(server);
    CloseVGS();
    return 0;
}