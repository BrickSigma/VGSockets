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
    VGSocket client;
    client.fd = StartupClient(8080, "127.0.0.1");
    if (client.fd == INVALID_SOCKET) {
        return -1;
    }
    InitVGSocket(&client);  // Initialize the VGSocket

    printf("Sending data...\n");
    int valsent = SendData(client.fd, "Hello server!", 14);
    if (valsent < 0) {
        return -1;
    }
    printf("Data sent! Number of bytes sent: %d\n", valsent);

    // Set the timeout duration for the TimedRecv function using
    // the Timer struct
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

    // Cleanup
    printf("Closing client and VGS...\n");
    CloseSocket(client.fd);
    CloseVGS();
    return 0;
}