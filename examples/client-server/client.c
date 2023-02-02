/****************************************************************************
 * 
 *  VGSockets core example - client code
 *  
 *  The code bellow creates a client that will connect to a server and send
 *  some data to it and in return receive some data.
 *
*****************************************************************************/

#include <stdio.h>

#include "../../src/vgs.h"

int main(void)
{
    // Initialize the library
    InitVGS();

    // Create a new socket and connect it to the server and port
    printf("Starting up client...\n");
    Socket client = StartupClient(8080, "127.0.0.1");
    if (client == INVALID_SOCKET) {
        return -1;
    }

    // Send and receive some data to and from the server
    printf("Sending data...\n");
    int valsent = SendData(client, "Hello server!", 14);
    if (valsent < 0) {
        return -1;
    }
    printf("Data sent! Number of bytes sent: %d\n", valsent);

    char buff[256];
    printf("Waiting for server...\n");
    int valread = RecvData(client, buff, 256);
    if (valread <= 0) {
        return -1;
    }
    printf("Data received: %s. \nNumber of bytes received: %d\n", buff, valread);

    // Cleanup
    printf("Closing client and VGS...\n");
    CloseSocket(client);
    CloseVGS();
    return 0;
}