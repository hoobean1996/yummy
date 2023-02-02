# Internet Domain Socket

## Byte Order

IP addresses and port number are integer values.

Most Significant Byte first -> `Big Endian`

the byte order used on a particular machine is called `host byte order`

`network byte order` 

```c++
#include <arpa/inet.h>

// host to network
uint16_t htons(uint16_t host_uint16);

uint32_t htonl(uint32_t host_uint32);

uint16_t ntohs(uint16_t net_uint16);

uint32_t ntohl(uint32_t net_uint32);
```

## data representation
the sender must encode data according to this convertion, while the receiver decodes following the same convention. 
`marshaling` and `unmarshaling`
Typically, these standards define a fixed format for each data type.

one simpler approach than marshalling is encode all transmitted data in text form, with separte data items delimited by a character.
we use `telnet` to debug an application.

## internet socket addresses
```c++

struct in_addr {
  in_addr_t s_addr;
};

struct sockaddr_in {
  sa_family sin_family;
  in_port_t sin_port;
  struct in_addr sin_addr;
  unsigned char __pad[X];
};

struct in6_addr {
  uint8_t s6_addr[16];
};

struct sockaddr_in6 {
  sa_family sin6_family;
  in_port_t sin6_port;
  uint32_t  sin6_flowinfo;
  struct in6_addr sin6_addr;
  uint32_t sin6_scope_id;
};
```


```c++
const struct in6_addr in6addr_any = IN6ADDR_ANY_INIT;

struct sockaddr_in6 addr;

memset(&addr, 0, sizeof(struct sockaddr_in6));
addr.sin6_family = AF_INET6;
addr.sin6_addr = in6addr_any;
addr.sin6_port = htons(port);

```

with IPv6 socket API, the new generic `sockaddr_storage` was introduced.

```c++
#define __s_aligntype uint32_t 

struct sockaddr_storage {
  sa_family_t ss_family;
  __ss_aligntype __ss_align;
  char __ss_padding[SS_PADSIZE];
};
```

## host and service apis
`inet_aton` and `inet_ntoa` function convert an IPv4 address in dotted-decimal notation to binary.

`inet_pton` and `inet_ntop` support IPv6 addresses.
```c++

#include <arpc/inet.h>

// p stands for `presentation` and the n stands for `network`
// p:
// 204.152.189.116 (IPv4 dotted-decimal address)
// ::1 (an IPv6 colon-separated hexadecimal address)
// ::FFFF:204.152.189.116 (an IPv4-mapped IPv6 address)
int inet_pton(int domain, const char *src_str, void *addrptr);

const char* inet_ntop(int domain, const void *addrptr, char *dst_str, size_t len);

```


`gethostbyname` returns the binary IP address corresponding to a hostname.

`getservbyname` returns the port number corresponding to a service name.

`gethostbyaddr` and `getservbyport` are reverse functions.

`getaddrinfo` modern successor to `gethostbyname` and `getservbyname`
`getnameinfo` perfoms the reverse translation.