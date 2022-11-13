# VGSockets
Video Game Sockets (aka VGSockets) is a sockets library currently being developed to make it easier to implement networking in video games.

## Current features
- Basic socket functions implemented like `bind`, `listen`, `accept`, `connect`, `send`, and `recv`.
- Automatic sever/client initialization function added to compress `bind`, `listen`, `accept`, and `connect` functions into one line.
- Cross-platform design for Windows and Linux.

## Future features
- Custom non-blocking sockets designed for use in continuously looping code. This type of socket will appropriately be called a `VGSocket`.
- Error checking system to ensure data is transmitted correctly and not cut off.

## Limitations
- Currently being designed to work with TCP connections only.
- Support on Mac has not been tested as of now, but will come soon.

## To-Do
- [ ] Add error return codes for each function call.
