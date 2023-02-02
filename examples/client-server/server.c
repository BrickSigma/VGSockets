/****************************************************************************
 * 
 *  VGSockets core example - server code
 *  
 *  The code bellow creates a server and waits for a client to connect.
 *  Once connected, the server will receive some data and respond to the
 *  client.
 *
*****************************************************************************/

#include <stdio.h>

#include "../../src/vgs.h"

int main(void)
{
    // Initialize the library
    InitVGS();
    
    // Create a new socket and bind it to port 8080
    printf("Starting up server...\n");
    Socket server = StartupServer(8080, 1);
    if (server == INVALID_SOCKET) {
        return -1;
    }
    
    // Accept a client
    printf("Waiting for client...\n");
    Socket new_socket = AcceptClient(server);
    if (new_socket == INVALID_SOCKET) {
        return -1;
    }

    // Receive and send some data from and to the client
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

    // Cleanup
    printf("Closing server and VGS...\n");
    CloseSocket(new_socket);
    CloseSocket(server);
    CloseVGS();
    return 0;
}