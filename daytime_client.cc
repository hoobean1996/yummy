#include "glog/logging.h"
#include "src/core/core.h"
#include "src/core/core_socket.h"
#include <cerrno>
#include <cstring>
#include <iostream>
#include <netinet/in.h>
#include <ostream>
#include <string>
#include <strings.h>
#include <sys/socket.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  yummy::initYummy(argc, argv);

  int sockFd = socket(AF_INET, SOCK_STREAM, 0);

  struct sockaddr_in serverAddr;
  bzero(&serverAddr, sizeof(serverAddr));
  serverAddr.sin_family = AF_INET;
  serverAddr.sin_port = htons(8888);

  if (connect(sockFd, (struct sockaddr *)(&serverAddr), sizeof(serverAddr)) <
      0) {
    LOG(FATAL) << "connect failed"
               << " errno=" << strerror(errno);
  }

  int n;
  char recvbuf[10240];

  while ((n = read(sockFd, recvbuf, 10240)) > 0) {
    recvbuf[n] = '\0';
    std::cout << std::string(recvbuf) << std::endl;
  }

  return 0;
}