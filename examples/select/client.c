#include <stdio.h>

#include "../../src/vgs.h"

int main(void)
{
    // Enable internal error messages
    EnableErrorShow();

    printf("Initializing VGS...\n");
    InitVGS();

    printf("Starting up client...\n");
    VGSocket client;
    client.fd = StartupClient(8080, "127.0.0.1");
    if (client.fd == INVALID_SOCKET) {
        return -1;
    }
    InitVGSocket(&client);
    printf("Successfully connected to server!\n");

    printf("Sending data...\n");
    int valsent = SendData(client.fd, "Hello server!", 14);
    if (valsent < 0) {
        return -1;
    }
    printf("Data sent! Number of bytes sent: %d\n", valsent);

    char buff[256];
    Timer t = {.sec=3, .msec=0, .usec=0};
    printf("Waiting for server...\n");
    int valread = TimedRecv(client, client.fd, buff, 256, &t);
    if (valread == 0) {
        printf("Timed out!\n");
    } else if (valread < 0) {
        return -1;
    } else {
        printf("Data received: %s. \nNumber of bytes received: %d\n", buff, valread);
    }

    printf("Closing client and VGS...\n");
    CloseSocket(client.fd);
    CloseVGS();
    return 0;
}