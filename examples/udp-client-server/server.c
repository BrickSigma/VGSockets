/****************************************************************************
 * 
 *  VGSockets UDP and timeout example - server code
 *  
 *  The code bellow creates a UDP server and waits for a client to connect.
 *  It then delays the code for 5 seconds to demonstrate the timeout function
 *  for UDP sockets.
 *
*****************************************************************************/

#include <stdio.h>
#include <unistd.h>

#include "../../src/vgs.h"

int main(void)
{
    // Initialize the library
    InitVGS();
    
    // Create a new socket and bind it to port 8080
    printf("Starting up server...\n");
    Socket server = StartupServer(UDP, 8080, 1);
    if (server == INVALID_SOCKET) {
        return -1;
    }

    Sockaddr client_addr;

    // Receive and send some data from and to the client
    char buff[256];
    printf("Waiting for data...\n");
    int valread = RecvFrom(server, buff, 256, &client_addr);
    if (valread < 0) {
        return -1;
    }
    printf("Data received: %s \nNumber of bytes received: %d\n", buff, valread);

    printf("Waiting for 5 seconds...\n");
    sleep(5);
    printf("Sending data...\n");
    int valsend = SendTo(server, "Hello client!", 14, client_addr);
    if (valsend < 0) {
        return -1;
    }
    printf("Successfully sent! Number of bytes sent: %d\n", valsend);

    // Cleanup
    printf("Closing server and VGS...\n");
    CloseSocket(server);
    CloseVGS();
    return 0;
}