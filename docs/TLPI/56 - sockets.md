# sockets
Sockets are a method of IPC that allow data to be exchanged between applications.

Overview:
each application creates a socket.
the server binds its socket to a well-known address so that clients can locate it.
`fd = socket(domain, type, protocol)`

Modern operating systems support at least the following domains:
`AF_UNIX`: allows communication between applications on the same host
`AF_INET`: allows communication between applications running on hosts via IPv4 network
`AF_INET6`: allows communication between applications running on hosts via IPv6 network.
AF stands for address family.
PF stands for protocol family.

every sockets implementation provides at least two types of sockets
`SOCK_STREAM`: provides reliable delivery, connection oriented.
`SOCK_DGRAM`: provide non-reliable delivery, not connection oriented.

`reliable` means we are guaranteed that either the transmitted data will arrive intact at the receiving application exactly as it was transmitted by the sender.
`Bidirectional`
`Byte-stream`

## Key System Calls
`socket`: creates a new socket
`bind`: binds a socket to an address
`listen`: allow a stream socket to accept incoming connections
`accept`: accepts a connect from a peer applicatioin on a listening stream socket
`connect`: establishes a connection with another socket

Socket I/O can be performed using the conventonal 
`read`, `write`
or 
socket-specific `send`, `recv`, `sendto`, `recvfrom`
by default, all system calls are `blocking`.
use `fnctl` to enable `non-blocking` I/O

in Linux: `ioctl(fd, FIONREAD, cnt)` to obtain the number of unread bytes available on the stream socket.

## create a socket
```c++
#include <sys/socket.h>

int socket(int domain, int type, int protocol);

// type | SOCK_CLOEXEC | SOCK_NONBLOCK

// use SOCK_NONBLOCK can save extra calls to `fcntl`
```

## Bind a socket to an address
```c++
#include <sys/socket.h>

int bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen);

```

`struct sockaddr` is a generic socket address structure.

```c++
struct sockaddr {
  sa_family_t sa_family;
  char        sa_data[14];
};
```

## active and passive sockets
stream sockets are often distinguished as being either active or passive.
by default, a socket has been created using `socket` is active.
an active socket can be used in a `connect` call to establish a connection to a passive socket. (active open)

a passive socket is one that has been marked to allow incoming via `listen`. (passive open)

## listen for incoming connections
```c++
#include <sys/socket.h>

int listen(int sockfd, int backlog);
```

backlog: when client call `connect`, before connection established, they are `pending connection`
the kernel must record some information about each pending connection request so that accept can be processed.
the `backlog` allows us to limit the number of such `pending connections`


## accept a connect
```c++
#include <sys/socket.h>

int accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen);
```
accept creates a new socket, and the new socket is connected to the peer socket.
the listen socket remains open, and can be used to accept further connections.

the `addrlen` is a value-result argument, it points to an integer.
so that the kernel knows how much space is avaialble to return the socket address, upon return from accept, this integer is set to indicate the number of bytes of data actually copied into the buffer.

## connect to a peer socket

```c++
#include <sys/socket.h>

int connect(int sockfd, const struct sockaddr* addr, socklen_t addrlen);

```

## connection termination: close
the usual way of terminating a stream socket is call `close`. If multiple fd refer to the same socket, then the connection is terminated when all of fd are closed.

suppose that, after we close a connection, the peer application crashes,and doesn't read the data we sent before, in this case, we have no way to know that.

so we introduce the `shutdown` systemcall, which provides finer control of how a steram socket connection is closed.

## SOCK_DGRAM
1. socket
2. bind
3. no listen and no accept required
   
## Exchange datagrams
```c++
#include <sys/socket.h>

ssize_t recvfrom(int sockfd, void *buffer, size_t length, int flags,
  struct sockaddr* src_addr,
  socklen_t *addrlen);

ssize_t sendto(int sockfd, const void *buffer, size_t length, int flags,
  struct sockaddr *dest_addr,
  socklen_t addrlen);
```
the src_addr and addrlen return the address of the remote socket used to send the datagram.


## use connect with datagram socket
even though datagram sockets are connectionless, 
the connect serves a purpose when applied to datagram sockets.
call connect to a datagram socket will let the kernel to record a particular address,
`connected datagram socket`

after connected,
datagrams can be sent througg `write` or `send`

only datagrams sent by peer socket may be read on the socket.

`asymmetric`, so we need to take both on two side sockets.