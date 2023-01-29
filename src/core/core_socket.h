#pragma once
#include "core.h"
#include <bits/stdint-uintn.h>
namespace yummy {

// An `fcntl` `F_SETOWN` operation can used to specify a process or process
// group to receive a `SIGURG` signal when the out-of-band data arrives or a
// `SIGPIPE` when a `SOCK_STREAM` breaks.
namespace net {

// createSocket: create a socket by ::socket
// @domain: communication domain
//  - AF_UNIX, AF_LOCAL: Local communication
//  - AF_INET: IPv4 Intenet
//  - AF_INET6: IPv6 Intenet
//  - AF_PACKET
// @type:
//  - SOCK_STREAM: Full-deplex byte steam.
//    Protocols which implements a SOCK_STREAM ensure that data is not lost or
//    duplicated. If a piece of data for which the peer protocol has buffer
//    space can not be successfully transmitted within a reasonable length of
//    time, then the connection is considered `dead`
//    When `SO_KEEPALIVE` is enabled on the socket the protocol checks in a
//    protocol-specific. A `SIGPIPE` is raised if a process sends or receives on
//    a broken stream, this usually causes naive process to exit.
//  - SOCK_DGRAM
//  - SOCK_SEQPACKET
//  - SOCK_RAW
// we can use bit OR of any of the following value to specify socket behaviour.
//  - SOCK_NONBLOCK
//  - SOCK_CLOEXEC
// @protocol:
//  - TCP
// @returns:
//  - EACCES: Permission issue
//  - EAFNOSUPPORT: The family does not support
//  - EINVAL: Unknown protocol, or family, or type
//  - EMFILE: the per-process limit on the number of open file descriptors has
//  been reached or the system-wide limit on the number of open file descriptors
//  has been reached
//  - ENOBUFS or ENOMEM: resource is not enough
//  - EPROTONOSUPPORT: the protocol does not support
fd createSocket(int domain, int type, int protocol);

fd createTCPSocket();

addr createAddr(uint16_t port);
} // namespace net
} // namespace yummy