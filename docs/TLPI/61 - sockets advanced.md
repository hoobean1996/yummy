# sockets advanced

## partial read and writes on stream sockets
a partial read may occru if there are fewer bytes available in the socket than were requested in the `read` call.
in this case, `read` returns the number of bytes available.

a partial write may occur if there is insufficient buffer space to transfer all of the requested bytes and one of the following is true
  - a signal handler interrupted the `write` call after it transferred some of the requested bytes
  - the socket was operating in nonblocking mode, and it was possible to transfer only some of the requested bytes
  - An asynchronous error occured after only some of the requrested bytes had been transferred.


```c++
ssize_t readn(int fd, void *buffer, size_t count) {
  ssize_t numRead;
  size_t totRead;

  char *buf;
  for(totRead = 0; totRad <n;) {
    numRead = read(fd, buf, n - totRead);
    if (numRaed == 0) return totRead; // EOF
    if (numRead == -1) {
      if (errno == ENTR) {
        continue; // Interrupted -- restart read
      }
      else return -1;
    }
    totRead += numRead;
    buf += numRead;
  }

  return totRead; // must be n bytes
}

ssize_t writen(int fd, void *buffer, size_t count) {
  ssize_t numWritten;
  size_t totWritten;

  const char *buf;

  for(totWritten = 0; totWritten < n;) {
    numWritten = write(fd, buf, n - totWritten);
    if (numWritten <=0 ) {
      if (numWritten == -1 && errno == EINTR) {
        //interrupted 
        continue;
      }
      else return -1;
      totWritten += numWritten;
    }

    return totWritten; // must be nbytes 
  }
}
```
wrap read and write to enable resume system calls.


# shutdown system call
```c++
#include <sys/socket.h>

int shtudown(int sockfd, int how);
```
the `shutdown` system call closes one ore both channels of the socket sockfd, depending on the value of `how`
- SHUT_RD: close the reading half of the connection. subsequent reads will return EOF. Data can still be written to the socket.AAfter a `SHUT_RD` on a UNIX domain stream socket, the pper application receives `SIGPIPE` signal and the `EPIPE` error, 
- SHUT_WR: clse the writing half of the connection.
- SHUW_RDWR


## socket-specific i/o

```c++
#include <sys/socket.h>

ssize_t recv(int sockfd, void *buffer, size_t length, int flags);

ssize_t send(int sockfd, const void *buffer, size_t length, int flgas);
```


## sendfile
application such as webservers and file servers frequently need to transfer the unalter contents of a disk file through a socket.

```c++
  while((n = read(diskfilefd, buf, BUF_SIZE))  > 0) write(sockfd, buf, n);
```
If we want to transfer large files via a socket, this technique is ineffcient.
1. one to copy file contents from the kernel buffer cache into user space
2. aother to copy user-space buffer back to the kernel space in order to transimitted via the socket.

The `sendfile` is designed to eliminated this inefficiency, when an application calls `sendfile` the file contents are transferred directly to the socket, without passing through user space.
`zero-copy` transfer.

```c++
#include <sys/sendfile.h>

// only works for send file to socket.
ssize_t sendfile(int out_fd, int in_fd, off_t *offset, size_t count);

```

## retrieve socket address

```c++
#include <sys/socket.h>

int getsockname(int sockfd, struct sockaddr *addr, socklen_t *addrlen);
int getpeername(int sockfd, struct sockaddr *addr, socklen_t *addrlen);

```


## TIME_WAIT
the TCP TIME_WAIT state is a frequent source of confusion in network programming.
the `TIME_WAIT` state serve two purposes:
- to implement reliable connection termination
- to allow expiration of old duplicate segment in the network so that they are not accepted by a new incarnation of the connection

## netstat monitor sockets
netstat -a : display all sockets
netstat -e: display extends information
netstat -c: display socket information continuously
netstat -l: display infromation about listening sockets
netstat -n: display ip address, ports numbers
netstat -p: show process id and name of program
netstat --inet: show ip sockets
netstat --tcp: show tcp sockets
netstat --udp: show udp sockets
netstat --unix: show unix sockets


## tcpdump monitor tcp traffic
src > dst: flags data-seqno ack window urg <options>


## socket options
socket options affect various features of the operation of a socket.

```c++
#include <sys/socket.h>

int getsockopt(int sockfd, int leve, int optname, void *optval, socklen_t *opt_len);

int setsockopt(int sockfd, int level, int optname, void *optval, socklen_t optlen);
```

`SO_REUSEADDR` serves a number of purposes
- to avoid `EADDDRINUSE` error when a TCP server is restarted and tries to bind a socket to a port that currently has an associted TCP.
  
```c++

if (setsockopt(sockfd, SOL_SOCKET, SQ_REUSEADDR, &optval, ...))

```

## Out-of-Bdan Data
out-of-band data is a feature of stream sockets that allows a sender to mark transimitted data as high pririty.
the receiver can obtain notificatioin of the availability of out-of-band data without needing to read all of the intervening data in the stream.

`telnet`, `rlogin`, and `ftp` to make it possible to abort previously transmitted commands.

`Out-of-band` data is sent and received using the `MSG_OOB` flag in the calls to `send` and `recv`


## sendmsg and recvmsg

the `sendmsg` and `recvmsg` system calls are the most general purpose of the socket I/O system calls.
can do everything that is done by `write` and `send`, `sendto`...
in addition:
- perform scatter-gather I/O, as with `readv` and `writev`
- we can tansmit messages containing domain-specifi `ancillary data` (control information)
  - for example, passing file descriptors
  - receive sender credentials