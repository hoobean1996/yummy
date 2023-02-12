
#include <cerrno>
#include <glog/logging.h>
#include <netinet/in.h>
#include <strings.h>
#include <sys/socket.h>

int main(int argc, char *argv[]) {
  int listenFd = socket(AF_INET, SOCK_STREAM, 0);
  if (listenFd < 0) {
    LOG(FATAL) << "create socket failed";
  }
  struct sockaddr_in serverAddr;
  bzero(&serverAddr, sizeof(serverAddr));
  serverAddr.sin_family = AF_INET;
  serverAddr.sin_addr.s_addr = htonl(0x7f000001);
  serverAddr.sin_port = htons(8888);
  if (bind(listenFd, (struct sockaddr *)(&serverAddr), sizeof(serverAddr)) <
      0) {
    LOG(FATAL) << "bind failed:" << errno;
  }
  if (listen(listenFd, 1024) < 0) {
    LOG(FATAL) << "listen failed";
  }
  for (;;) {
    socklen_t cliLen = sizeof(struct sockaddr_in);
    int connFd = accept(listenFd, (struct sockaddr *)(&serverAddr),
                        (socklen_t *)&cliLen);
    if (connFd < 0) {
      LOG(FATAL) << "accept failed";
    }
    LOG(ERROR) << "accept successfully";
  }
  return 0;
}