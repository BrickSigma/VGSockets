#ifndef VGS_H
#define VGS_H

#ifdef __cplusplus
extern "C" {
#endif

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


// VGSocket related definitions
#undef FD_SETSIZE
#define FD_SETSIZE      (64)  // Maximum file descriptor set size

typedef struct _VGSocket {
    Socket fd;
    unsigned int fd_count;
    Socket fd_array[FD_SETSIZE];
} VGSocket;

typedef struct _Timer {
    long sec;
    long msec;
    long usec;
} Timer;


// ============== CORE MODULES ================

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
 * @brief Create a server socket descriptor and bind it.
 * 
 * @param port Port to bind to
 * @param backlog Number of connections to listen to
 * 
 * @return On success, the server socket descriptor is returned.
 */
Socket StartupServer(int port, int backlog);

/**
 * @brief Accept any incoming connections from a client
 * 
 * @param fd Server socket
 * 
 * @return Socket descriptor of the new socket connected 
 */
Socket AcceptClient(Socket fd);

/**
 * @brief Create a client socket descriptor and connect it to a server
 * 
 * @param port Port to connect to
 * @param address IPv4 address of server
 * 
 * @return Socket descriptor
 */
Socket StartupClient(int port, char *address);

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
 * @return The number of bytes successfully sent. Return STATUS_ERROR on failure.
 */
int SendData(Socket fd, const void *buf, int len);

/**
 * @brief Read any incoming data and write to buf
 * 
 * @param fd Socket descriptor
 * @param buf 
 * @param len 
 * 
 * @return The number of bytes successfully received.
 */
int RecvData(Socket fd, void *buf, int len);


// ============== SELECT/FD_SET MODULES ================

/**
 * @brief Initialise VGSocket file descriptor set. This should be called after StartupServer
 * 
 */
void InitVGSocket(VGSocket *vgs);

/**
 * @brief Equivalent to FD_CLR in WinSock.h and sys/select.h
 * 
 * @param fd 
 * @param vgs 
 */
void ClearSet(Socket fd, VGSocket *vgs);

/**
 * @brief Equivalent to FD_ISSET in WinSock.h and sys/select.h
 * 
 * @param fd 
 * @param vgs 
 * @return int 
 */
int IsSet(Socket fd, VGSocket *vgs);

/**
 * @brief Equivalent to FD_SET in WinSock.h and sys/select.h
 * 
 * @param fd 
 * @param vgs 
 */
void AddSet(Socket fd, VGSocket *vgs);

/**
 * @brief Equivalent to FD_ZERO in WinSock.h and sys/select.h
 * 
 * @param vgs 
 */
void ZeroSet(VGSocket *vgs);


// ============== ERROR MODULES ================

/**
 * @brief Enable internal error messages.
 * 
 */
void EnableErrorShow(void);

/**
 * @brief Disable internal error messages. This is set by default.
 * 
 */
void DisableErrorShow(void);

#ifdef __cplusplus
}
#endif

#endif // VGS_H
