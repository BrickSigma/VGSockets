# VGSockets

# Contents
1. [Introduction](#introduction)  
2. [Current features](#current-features)  
3. [Future features](#future-features)  
4. [Examples](#simple-client-server-example)  
6. [Build and usage](#build-and-usage)
5. [To-Do](#to-do)

## Introduction
<b>VGSockets</b> stands for <b>Video Game Sockets</b>, and as the name suggests it is a library designed to make networking in video games and socket programming easier.  


## Current features
- Basic socket functions implemented like `bind`, `listen`, `accept`, `connect`, `send`, and `recv`.
- Automatic sever/client initialization function added to compress `bind`, `listen`, `accept`, and `connect` functions into one line.
- Cross-platform design for Windows and Linux.

## Future features
- Custom sockets designed for use in continuously looping code. This type of socket will appropriately be called a `VGSocket`.
- Error checking system to prevent data from being malformed and offset when transmitted/recieved continuously.

## Limitations
- Only TCP connections have been implemented as of now, but UDP will be added.
- This library has not been tested on MacOS, so support is undetermined at the moment.

## Simple client-server example
<b>All examples are in the `examples` folder</b>  
server.c:  
```
#include <stdio.h>
#include "vgs.h"

int main(void)
{
    printf("Initializing VGS...\n");
    InitVGS();
    
    printf("Starting up server...\n");
    Socket server = StartupServer(8080, 1);
    if (server == STATUS_ERROR) {
        return -1;
    }
    printf("Server started!\n");
    
    printf("Waiting for client...\n");
    Socket new_socket = AcceptClient(server);
    if (new_socket == STATUS_ERROR) {
        return -1;
    }
    printf("Client connected!\n");

    char buff[256];
    printf("Waiting for data...\n");
    int valread = RecvData(new_socket, buff, 256);
    if (valread <= 0) {
        return -1;
    }
    printf("Data received: %s. \nNumber of bytes received: %d\n", buff, valread);

    printf("Sending data...\n");
    int valsend = SendData(new_socket, "Hello client!", 14);
    if (valsend <= 0) {
        return -1;
    }
    printf("Successfully sent! Number of bytes sent: %d\n", valsend);

    printf("Closing server and VGS...\n");
    CloseSocket(new_socket);
    CloseSocket(server);
    CloseVGS();
    return 0;
}
```  
client.c:  
```
#include <stdio.h>
#include "vgs.h"

int main(void)
{
    printf("Initializing VGS...\n");
    InitVGS();

    printf("Starting up client...\n");
    Socket client = StartupClient(8080, "127.0.0.1");
    if (client == INVALID_SOCKET) {
        return -1;
    }
    printf("Successfully connected to server!\n");

    printf("Sending data...\n");
    int valsent = SendData(client, "Hello server!", 14);
    if (valsent < 0) {
        return -1;
    }
    printf("Data sent! \nNumber of bytes sent: %d\n", valsent);

    char buff[256];
    printf("Waiting for server...\n");
    int valread = RecvData(client, buff, 256);
    if (valread <= 0) {
        return -1;
    }
    printf("Data received: %s. Number of bytes received: %d\n", buff, valread);

    printf("Closing client and VGS...\n");
    CloseSocket(client);
    CloseVGS();
    return 0;
}
```

## Build and usage
Download the source code for the repository or use `git clone https://github.com/BrickSigma/VGSockets.git VGSockets`.  

Enter the `VGSockets/src` directory and run `make`. This will generate the static library for VGSockets.  

To use in your projects, add the `vgs.h` header and `libvgs.a` files to your project root directory as shown bellow:  
```
.
└── Project/
    ├── src/
    │   ├── server.c
    │   └── client.c
    ├── include/
    │   └── vgs.h
    ├── lib/
    │   └── libvgs.a
    └── Makefile
```  
And your Makefile should be like this:
```
CC := gcc
SRC := src/
LDFLAGS := -L./lib -lvgs
INCLUDE := -I./include

ifeq ($(OS), Windows_NT)
	LDFLAGS += -lws2_32
	EXT += .exe
else
	EXT += .out
endif

build:
	$(CC) $(SRC)server.c -o server$(EXT) $(INCLUDE) $(LDFLAGS)
	$(CC) $(SRC)client.c -o client$(EXT) $(INCLUDE) $(LDFLAGS)
```

## To-Do
:white_check_mark: Add error return codes for each function call.  
:white_check_mark: Add option to turn on/off error messages.
:white_check_mark: Add `select` function variant.
:white_check_mark: Add custom VGSocket datatype to allow Recv to timeout.
- [ ] Add error checking protocol to prevent TCP stream receiving next packet of data when session closed.  
- [ ] Add global error values for user reference.  
- [ ] Add UDP support.
- [ ] Create documentation/cheetsheet for functions and structures.
