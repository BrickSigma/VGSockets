/****************************************************************************
 * 
 *  VGSockets timeout example - client code
 *  
 *  The code bellow creates a client that will connect to a server.
 * 
 *  Once the two are connected the client will wait to recieve data with
 *  TimedRecv, which will timeout after 3 seconds if no data is recieved.
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
    Socket client;
    client = StartupClient(8080, "127.0.0.1");
    if (client == INVALID_SOCKET) {
        return -1;
    }

    printf("Sending data...\n");
    int valsent = SendData(client, "Hello server!", 14);
    if (valsent < 0) {
        return -1;
    }
    printf("Data sent! Number of bytes sent: %d\n", valsent);

    // Set the timeout duration for the TimedRecv function using
    // the Timer struct
    char buff[256];
    printf("Waiting for server...\n");
    int valrecv = TimedRecv(client, buff, 256, 3000);  // Recv set to timeout after 3 seconds
    if (valrecv < 0) {
        perror("Error in receiving data");
    } else if (valrecv == 0) {
        printf("Timed out.\n");
    } else {
        printf("Date received: %s\n", buff);
    }
    

    // Cleanup
    printf("Closing client and VGS...\n");
    CloseSocket(client);
    CloseVGS();
    return 0;
}