#ifndef VGS_H
#define VGS_H

#ifdef __cplusplus
extern "C" {
#endif

// SOCKET MACROS

/**
 * @brief Socket descriptor
 * 
 */
typedef unsigned long long Socket;

// Return codes
#undef STATUS_ERROR
#undef STATUS_SUCCESS
#undef INVALID_SOCKET

#define STATUS_ERROR        (-1)            // Error return code
#define STATUS_SUCCESS      (0)             // Success return code
#define INVALID_SOCKET      (Socket)(~0)    // Invalid socket return code

enum __SocketType {
    TCP = 1, // TCP Socket type
    UDP = 2, // UPD Socket type
};

typedef struct __Sockaddr {
    unsigned short port;
    unsigned int addr;
} Sockaddr;


// STRUCTURES/MACROS/TYPEDEFS FOR POLL-BASED FUNCTIONS

// Equivilent to pollfd on UNIX and Win32 API
typedef struct __Pollfd {
    Socket fd;      // File descriptor
    short events;   // Requested events
    short revents;  // Returned events
} Pollfd;

#undef POLLIN
#undef POLLPRI
#undef POLLOUT
#undef POLLERR
#undef POLLHUP
#undef POLLNVAL

#if defined _WIN32 || defined __CYGWIN__
    #define POLLIN (0x0100 | 0x0200)  // There is data to read.
    #define POLLPRI (0x0400)  // There is urgent data to read.
    #define POLLOUT (0x0010)  // Writing now will not block.
    #define POLLERR (0x0001)  // Error condition.
    #define POLLHUP (0x0002)  // Hung up.
    #define POLLNVAL (0x0004)  // Invalid polling request.
#else
    #define POLLIN (0x001)  // There is data to read.
    #define POLLPRI (0x002)  // There is urgent data to read.
    #define POLLOUT (0x004)  // Writing now will not block.
    #define POLLERR (0x008)  // Error condition.
    #define POLLHUP (0x010)  // Hung up.
    #define POLLNVAL (0x020)  // Invalid polling request.
#endif


// ============== CORE FUNCTIONS ================

/**
 * @brief Initialize the library.
 * 
 */
int InitVGS(void);

/**
 * @brief Close the library
 * 
 */
int CloseVGS(void);

/**
 * @brief Create a server socket descriptor and binds it to the specified port.
 * 
 * @param type Either TCP or UDP server
 * @param port Port to bind to
 * @param backlog Number of connections to listen to. Ignored if UDP is used.
 * 
 * @return On success, the server socket descriptor is returned. On failure, INVALID_SOCKET is returned.
 */
Socket StartupServer(int type, int port, int backlog);

/**
 * @brief Accept any incoming connections from a client
 * 
 * @param fd Server socket
 * 
 * @return Socket descriptor of the new socket connected. On failure, INVALID_SOCKET is returned.
 */
Socket AcceptClient(Socket fd);

/**
 * @brief Create a TCP client socket descriptor and connect it to a server
 * 
 * @param type Either TCP or UDP client
 * @param address Sockaddr address of server to connect to
 * 
 * @return Socket descriptor. On failure, INVALID_SOCKET is returned.
 */
Socket StartupClient(int type, Sockaddr address);

/**
 * @brief  Convert an IPv4 address to an unsigned 32 bit value. Similar to `inet_addr`.
 * 
 * @param  address
 *  
 * @retval 32 bit integer address
 */
unsigned int IpAddr(const char *address);

/**
 * @brief  Create an address variable for a socket
 * 
 * @param  port: Port number, eg port `8080`
 * @param  address: IPv4 address
 * 
 * @retval A new Sockaddr variable
 */
Sockaddr LoadAddr(int port, const char *address);

/**
 * @brief Close the socket
 * 
 * @param fd 
 */
int CloseSocket(Socket fd);

/**
 * @brief Send the data in buf.
 * 
 * @param fd Socket descriptor
 * @param buf 
 * @param len 
 * 
 * @return The number of bytes successfully sent. Returns STATUS_ERROR on failure.
 */
int SendData(Socket fd, const void *buf, int len);

/**
 * @brief  Equivilent to sendto in UNIX/Win32
 * 
 * @param  fd Socket file descriptor
 * @param  buf
 * @param  len
 * @param  address Address of destination socket
 * 
 * @retval The number of bytes successfully sent. Returns STATUS_ERROR on failure.
 */
int SendTo(Socket fd, const void *buf, int len, Sockaddr address);

/**
 * @brief Read any incoming data and write to buf
 * 
 * @param fd Socket descriptor
 * @param buf 
 * @param len 
 * 
 * @return The number of bytes successfully received. Returns STATUS_ERROR on failure.
 */
int RecvData(Socket fd, void *buf, int len);

/**
 * @brief  Equivilent to recvfrom in UNIX/Win32
 * 
 * @param  fd Socket file descriptor
 * @param  buf
 * @param  len
 * @param  address Address of source socket
 * 
 * @retval The number of bytes successfully received. Returns STATUS_ERROR on failure.
 */
int RecvFrom(Socket fd, void *buf, int len, Sockaddr *address);



// ============== POLL/TIMEOUT FUNCTIONS ================

/**
 * @brief  Exactly the same as poll on UNIX and Win32 API
 * 
 * @param  fds Array of poll file descriptors 
 * @param  nfds Size of the array
 * @param  timeout Timeout in milliseconds.
 * @return The number of file descriptors who have an updated event. Returns -1 on error and errno is set. 
 */
int Poll(Pollfd *fds, unsigned long nfds, int timeout);

/**
 * @brief  Adds a timeout to receiving data. Similar to using select/poll. Only works with TCP sockets.
 * 
 * @note To use with UDP sockets, use the `TimedRecvFrom` function.
 * 
 * @param  fd: Socket descriptor
 * @param  buf: Pointer to destination buffer
 * @param  len: Length of buffer
 * @param  timeout: Amount of time to delay in milliseconds. If -1 is equal to RecvData. If 0 it will immediately timeout.
 * @retval Number of bytes received on success. Returns 0 is timed out. Returns -1 if an error occured.
 */
int TimedRecv(Socket fd, void *buf, int len, int timeout);

/**
 * @brief  Adds a timeout to receiving data from UDP sockets.
 * 
 * @param  fd: Socket descriptor
 * @param  buf: Pointer to destination buffer
 * @param  len: Length of buffer
 * @param address: Address of source socket
 * @param  timeout: Amount of time to delay in milliseconds. If -1 is equal to RecvData. If 0 it will immediately timeout.
 * @retval Number of bytes received on success. Returns 0 is timed out. Returns -1 if an error occured.
 */
int TimedRecvFrom(Socket fd, void *buf, int len, Sockaddr *address, int timeout);


// ============== ERROR FUNCTIONS ================

/**
 * @brief Enable automatic internal error messages.
 * 
 */
void EnableErrorShow(void);

/**
 * @brief Disable automatic internal error messages. This is set by default.
 * 
 */
void DisableErrorShow(void);

/**
 * @brief Output the error code/message from the last function call.
 * 
 * @param msg 
 */
void ShowError(const char *msg);

#ifdef __cplusplus
}
#endif

#endif // VGS_H
