# ip

```c++

socket(int socket_family, int socket_type, int protocol);

tcp_socket = socket(AF_INET, SOCK_STREAM, 0);
udp_socket = socket(AF_INET, SOCK_DGRAM, 0);
raw_socket = socket(AF_INET, SOCK_RAW, protocol);

```

It is possible to do nonblocking I/O on sockets by setting the `O_NONBLOCK` flag on the socket file using `fcntl`.

       ┌────────────────────────────────────────────────────────────────┐
       │                          I/O events                            │
       ├───────────┬───────────┬────────────────────────────────────────┤
       │Event      │ Poll flag │ Occurrence                             │
       ├───────────┼───────────┼────────────────────────────────────────┤
       │Read       │ POLLIN    │ New data arrived.                      │
       ├───────────┼───────────┼────────────────────────────────────────┤
       │Read       │ POLLIN    │ A connection setup has been completed  │
       │           │           │ (for connection-oriented sockets)      │
       ├───────────┼───────────┼────────────────────────────────────────┤
       │Read       │ POLLHUP   │ A disconnection request has been       │
       │           │           │ initiated by the other end.            │
       ├───────────┼───────────┼────────────────────────────────────────┤
       │Read       │ POLLHUP   │ A connection is broken (only for       │
       │           │           │ connection-oriented protocols).  When  │
       │           │           │ the socket is written SIGPIPE is also  │
       │           │           │ sent.                                  │
       ├───────────┼───────────┼────────────────────────────────────────┤
       │Write      │ POLLOUT   │ Socket has enough send buffer space    │
       │           │           │ for writing new data.                  │
       ├───────────┼───────────┼────────────────────────────────────────┤
       │Read/Write │ POLLIN |  │ An outgoing connect(2) finished.       │
       │           │ POLLOUT   │                                        │
       ├───────────┼───────────┼────────────────────────────────────────┤
       │Read/Write │ POLLERR   │ An asynchronous error occurred.        │
       ├───────────┼───────────┼────────────────────────────────────────┤
       │Read/Write │ POLLHUP   │ The other end has shut down one        │
       │           │           │ direction.                             │
       ├───────────┼───────────┼────────────────────────────────────────┤
       │Exception  │ POLLPRI   │ Urgent data arrived.  SIGURG is sent   │
       │           │           │ then.                                  │
       └───────────┴───────────┴────────────────────────────────────────┘


       - sockaddr: generic descriptor for any kind of socket operation
       - sockaddr_in: struct specific to IP-based communicatiioin