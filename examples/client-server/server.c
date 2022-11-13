#include <stdio.h>

#include "../../src/vgs.h"

int main(void)
{
    printf("Initializing VGS...\n");
    InitVGS();
    
    printf("Starting up server...\n");
    Socket server = StartupServer(8080, 1);
    printf("Server started!\n");
    
    printf("Waiting for client...\n");
    Socket new_socket = AcceptClient(server);
    printf("Client connected!\n");

    char buff[256];
    printf("Waiting for data...\n");
    int valread = RecvData(new_socket, buff, 256);
    printf("Data received: %s. Number of bytes received: %d\n", buff, valread);

    printf("Sending data...\n");
    int valsend = SendData(new_socket, "Hello client!", 14);
    printf("Successfully sent! Number of bytes sent: %d\n", valsend);

    printf("Closing server and VGS...\n");
    CloseSocket(new_socket);
    CloseSocket(server);
    CloseVGS();
    return 0;
}