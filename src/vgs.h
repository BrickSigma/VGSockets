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
#undef SETSIZE

#ifdef _WIN32  // Windows set system

    #define SETSIZE     (64)    // Maximum file descriptor set size

    //Equivelent to fd_set type in WinSock.h and sys/socket.h
    typedef struct __VGSet {
        unsigned int fd_count;
        Socket fd_array[SETSIZE];
    } VGSet;
#else  // UNIX set system
    // Taken from sys/select.h
    #define SETSIZE      (1024)  // Maximum file descriptor set size

    typedef unsigned int __mask;
    #define	__howmany(x, y)	(((x) + ((y) - 1)) / (y))

    //Equivelent to fd_set type in WinSock.h and sys/socket.h
    typedef struct __VGSet {
        __mask __fds_bits[__howmany(SETSIZE, (8 * (unsigned) sizeof(__mask)))];
    } VGSet;
#endif

/**
 * @brief Contains the server/client socket descriptors along with a read file descriptor set.
 * 
 */
typedef struct _VGSocket {
    Socket fd;
    Socket max_fd;
    VGSet set;
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
 */
void ClearSet(Socket fd, VGSet *set);

/**
 * @brief Equivalent to FD_ISSET in WinSock.h and sys/select.h
 * 
 */
int IsSet(Socket fd, VGSet *set);

/**
 * @brief Equivalent to FD_SET in WinSock.h and sys/select.h
 * 
 */
void AddSet(Socket fd, VGSet *set);

/**
 * @brief Equivalent to FD_ZERO in WinSock.h and sys/select.h
 * 
 */
void ZeroSet(VGSet *set);

/**
 * Equivalent to select in WinSock.h and sys/select.h
 * 
 * @note Unlike WinSock and UNIX select, the timeout variable is not changed and can be reused.
 * 
 */
int VGSelect(int nfds, VGSet *readfds, VGSet *writefds, VGSet *exceptfds, Timer *timer);

/**
 * @brief Combination of VGSelect and RecvData, allowing for Recv to timeout
 * 
 * @return The number of bytes received. Returns 0 on timeout and -1 on error
 */
int VGSRecv(VGSocket vgs, Socket fd, void *buf, int len, Timer *timer);


// ============== ERROR MODULES ================

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
