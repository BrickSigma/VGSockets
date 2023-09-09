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

#define POLLIN 0x001  // There is data to read.
#define POLLPRI 0x002  // There is urgent data to read.
#define POLLOUT 0x004  // Writing now will not block.
#define POLLERR 0x008  // Error condition.
#define POLLHUP 0x010  // Hung up.
#define POLLNVAL 0x020  // Invalid polling request.


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
 * @brief Create a server socket descriptor and bind it.
 * 
 * @param port Port to bind to
 * @param backlog Number of connections to listen to
 * 
 * @return On success, the server socket descriptor is returned. On failure, INVALID_SOCKET is returned.
 */
Socket StartupServer(int port, int backlog);

/**
 * @brief Accept any incoming connections from a client
 * 
 * @param fd Server socket
 * 
 * @return Socket descriptor of the new socket connected. On failure, INVALID_SOCKET is returned.
 */
Socket AcceptClient(Socket fd);

/**
 * @brief Create a client socket descriptor and connect it to a server
 * 
 * @param port Port to connect to
 * @param address IPv4 address of server
 * 
 * @return Socket descriptor. On failure, INVALID_SOCKET is returned.
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
 * @return The number of bytes successfully sent. Returns STATUS_ERROR on failure.
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
 * @brief  Adds a timeout to receiving data. Similar to using select/poll.
 * 
 * @param  fd: Socket descriptor
 * @param  buf: Pointer to destination buffer
 * @param  len: Length of buffer
 * @param  timeout: Amount of time to delay in milliseconds. If -1 is equal to RecvData. If 0 it will immediately timeout.
 * @retval Number of bytes received on success. Returns 0 is timed out. Returns -1 if an error occured.
 */
int TimedRecv(Socket fd, void *buf, int len, int timeout);


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
