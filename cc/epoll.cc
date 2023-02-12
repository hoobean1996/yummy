#include <cstdio>
#include <cstring>
#include <stdio.h>
#include <sys/epoll.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  const int kMaxEvents = 10;
  struct epoll_event ev;
  struct epoll_event events[kMaxEvents];

  // ::socket
  //   AF_UNIX: Local communication
  //
  int serverSocket = ::socket(AF_UNIX, SOCK_STREAM, 0);
  if (serverSocket == -1) {
    perror("create socket failed");
    return 1;
  }

  struct sockaddr_un localAddr;
  memset(&localAddr, 0, sizeof(localAddr));
  localAddr.sun_family = AF_UNIX;
  strncpy(localAddr.sun_path, "local.sock", sizeof(localAddr.sun_path) - 1);

  if (::bind(serverSocket, (struct sockaddr *)&localAddr, sizeof(localAddr)) ==
      -1) {
    perror("bind socket failed");
    return 1;
  }

  const int kListenBacklog = 50;
  if (::listen(serverSocket, kListenBacklog) == -1) {
    perror("listen socket failed");
    return 1;
  }

  struct sockaddr_un peerAddr;
  socklen_t peerAddrSize = sizeof(peerAddr);
  int clientSocket =
      ::accept(serverSocket, (struct sockaddr *)&peerAddr, &peerAddrSize);
  return 0;
}