#include <stdio.h>

#include "../../src/vgs.h"

int main(void)
{
    printf("Initializing VGS...\n");
    InitVGS();

    printf("Starting up client...\n");
    Socket client = StartupClient(8080, "192.168.1.15");
    printf("Successfully connected to server!\n");

    printf("Sending data...\n");
    int valsent = SendData(client, "Hello server!", 14);
    printf("Data sent! Number of bytes sent: %d\n", valsent);

    char buff[256];
    printf("Waiting for server...\n");
    int valread = RecvData(client, buff, 256);
    printf("Data received: %s. Number of bytes received: %d\n", buff, valread);

    printf("Closing client and VGS...\n");
    CloseSocket(client);
    CloseVGS();
    return 0;
}