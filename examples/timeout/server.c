/****************************************************************************
 * 
 *  VGSockets timeout example - server code
 *  
 *  The code bellow creates a server that will connect to a client.
 * 
 *  Once the two are connected the client will send some data to the server. 
 *  The server will then delay for 5 seconds as the client waits for a response 
 *  so that the timeout functionality of the client can be demonstrated.
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
    Socket server = StartupServer(TCP, 8080, 1);
    if (server == INVALID_SOCKET) {
        return -1;
    }
    
    // Accept a client
    printf("Waiting for client...\n");
    Socket new_socket = AcceptClient(server);
    if (new_socket == INVALID_SOCKET) {
        return -1;
    }

    // Receive any incomming data from the client
    char buff[256];
    int valread = RecvData(new_socket, buff, 256);
    if (valread < 0) {
        return -1;
    }
    printf("Data received: %s. \nNumber of bytes received: %d\n", buff, valread);

    // Delay the code and send the data after delay
    printf("Delaying for 5 seconds...\n");
    sleep(5);
    printf("Sending data...\n");
    int valsend = SendData(new_socket, "Hello client!", 14);
    if (valsend < 0) {
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