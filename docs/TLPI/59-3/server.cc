#include "common.h"
#include <arpa/inet.h>
#include <cstdio>
#include <cstring>
#include <netinet/in.h>
#include <sys/socket.h>

int main(int argc, char *argv[]) {
  int sfd = socket(AF_INET6, SOCK_DGRAM, 0);
  if (sfd == -1) {
    return 1;
  }

  struct sockaddr_in6 svaddr;
  memset(&svaddr, 0, sizeof(struct sockaddr_in6));
  svaddr.sin6_family = AF_INET6;
  svaddr.sin6_addr = in6addr_any;
  svaddr.sin6_port = htons(PORT_NUM);

  if (bind(sfd, (struct sockaddr *)&svaddr, sizeof(struct sockaddr_in6)) ==
      -1) {
    return 1;
  }

  for (;;) {
    socklen_t len = sizeof(struct sockaddr_in6);
    struct sockaddr_in6 claddr;
    char buf[BUFSIZ];
    char claddrStr[46];
    int numBytes =
        recvfrom(sfd, buf, BUFSIZ, 0, (struct sockaddr *)&claddr, &len);
    if (inet_ntop(AF_INET6, &claddr.sin6_addr, claddrStr, 46) == nullptr) {
      return 1;
    }
  }

  return 0;
}