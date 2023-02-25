#include "acceptor.h"
#include "cc/src/cetty/addr.h"
#include "cc/src/cetty/channel.h"
#include "glog/logging.h"
#include <arpa/inet.h>
#include <cerrno>
#include <cstring>
#include <fcntl.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>

namespace cetty {

Acceptor::Acceptor(EventLoop *loop, Addr *addr, IAcceptorCallback *callback)
    : port_(addr->getPort()), listenFd_(-1), addr_(addr),
      serverSockChannel_(nullptr), callback_(callback), loop_(loop) {}

Acceptor::~Acceptor() { close(listenFd_); }

void Acceptor::start() {
  // listen on given ip and port, then create a Channel with
  // fd, and its event handler to poller.
  listenFd_ = listenOn();
  serverSockChannel_ = new Channel(loop_, listenFd_, this);
  serverSockChannel_->enableReading();
  LOG(ERROR) << "Acceptor is ready, waiting for new connection";
}

void Acceptor::handleReadEvent() {
  int connFd;
  struct sockaddr_in cliAddr;
  socklen_t cliLen = sizeof(struct sockaddr_in);
  connFd = accept(listenFd_, (sockaddr *)&cliAddr, (socklen_t *)&cliLen);
  fcntl(connFd, F_SETFL, O_NONBLOCK);
  char ip[INET_ADDRSTRLEN];
  inet_ntop(AF_INET, &(cliAddr.sin_addr), ip, INET_ADDRSTRLEN);
  LOG(ERROR) << "Acceptor accepts new connection, fd=" << connFd
             << ", client=" << ip << ":" << cliAddr.sin_port;
  callback_->handleNewConnection(connFd);
}

void Acceptor::handleWriteEvent() {}

const int kListenBacklog = 1024;

// listenOn will listen to a port, and return the fd.
int Acceptor::listenOn() {
  int on = 1;
  listenFd_ = socket(AF_INET, SOCK_STREAM, 0);
  struct sockaddr_in serverAddr;
  fcntl(listenFd_, F_SETFL, O_NONBLOCK);
  setsockopt(listenFd_, SOL_SOCKET, SO_REUSEADDR, &on, sizeof on);
  serverAddr.sin_family = AF_INET;
  serverAddr.sin_addr.s_addr = ::inet_addr(addr_->getIP().c_str());
  serverAddr.sin_port = htons(port_);
  int ret = bind(listenFd_, (struct sockaddr *)&serverAddr, sizeof serverAddr);
  if (ret == -1) {
    LOG(FATAL) << "bind failed, errno=" << ret
               << ", errmsg=" << strerror(errno);
  }
  ret = listen(listenFd_, kListenBacklog);
  if (ret == -1) {
    LOG(FATAL) << "listen failed, errno=" << ret
               << ", errmsg=" << strerror(ret);
  }
  return listenFd_;
}
} // namespace cetty