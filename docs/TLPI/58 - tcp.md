# IP
IP - the network layer, concerned with delivering packets from the source host to the destination host.
1. breaking data into fragments small enough for transimission via data-link-layer
2. routing data across the internet
3. providing services to the transport layer


a `SOCK_RAW` socket type which allows an application to communicate directly with the IP layer.

For example a `sendip` program which is a cli that allows the construction and transimission of IP datagrams.

## IP is connectionless and unrelaible
IP makes best effort to transmit datagrams from the sender to the receiver.
IPv4 provides a checksum for the IP header, which allows the detection of errors in the header, but doesn't provide any error detection for the data within the packet.


IPv4 datagrams <= 65535 bytes
IPv6 datagrams <=  65575 bytes (+40 for the header), provide `jumbograms` to support larger datagrams.

Data-link layers impose an upper limit (MTU) = 1500

when the IP datagrams > MTU, it splits to fragments.


## IPv4 address
network addr = 32 bits
  [network id] [host id]
network mast
  [network all 1s] [all 0s]

`INADDR_LOOPBACK` is defined in c
`INADDR_ANY` is wildcard address

`INADDR_ANY` is useful for applications that bind internet domain sockets on a `multi-homed` hosts. If an application on a multihomed hosts binds a socket to just one of its host's IP addresses, then the socket can receive only UDP or TCP connection requests to that IP address.

## IPv6 address
IPv6 are 128 bits.

F000:0:0:0:0:0:A:1

F000::A:1 

// :: to 0...

to communicate between IPv6 - IPv4, IPv6 address can work as IPv4-mapped

[80 bits 0] [16 bits F] [32 bits IPv4]