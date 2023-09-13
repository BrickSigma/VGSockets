/****************************************************************************
 * 
 *  VGSockets UDP and timeout example - client code
 *  
 *  The code bellow creates a UDP client that connects to the server.
 *  It uses the TimedRecvFrom function to add a timeout to receiving data
 *  and has been set to timeout after 3 seconds.
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
    Sockaddr server_addr = LoadAddr(8080, "127.0.0.1");
    Socket client = StartupClient(UDP, server_addr);
    if (client == INVALID_SOCKET) {
        return -1;
    }

    // Send and receive some data to and from the server
    printf("Sending data...\n");
    int valsent = SendTo(client, "Hello server!", 14, server_addr);
    if (valsent < 0) {
        return -1;
    }
    printf("Data sent! Number of bytes sent: %d\n", valsent);

    char buff[256];
    printf("Waiting for server...\n");
    int valrecv = TimedRecvFrom(client, buff, 256, &server_addr, 3000);
    if (valrecv < 0) {
        perror("Error in receiving data");
    } else if (valrecv == 0) {
        printf("Timed out.\n");
    } else {
        printf("Data received: %s\n", buff);
    }

    // Cleanup
    printf("Closing client and VGS...\n");
    CloseSocket(client);
    CloseVGS();
    return 0;
}