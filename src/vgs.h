#ifndef VGS_H
#define VGS_H

#ifndef STATUS_ERROR
#   define STATUS_ERROR (-1)
#endif

#ifndef STATUS_SUCCESS
#   define STATUS_SUCCESS (0)
#endif

/**
 * @brief Socket descriptor
 * 
 */
typedef unsigned long long Socket;

#ifndef INVALID_SOCKET
#   define INVALID_SOCKET (Socket)(~0)
#endif

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
 * @return The number of bytes successfully received. Return STATUS_ERROR on failure.
 */
int RecvData(Socket fd, void *buf, int len);

#endif // VGS_H
