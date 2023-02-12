#include "acceptor.h"
#include "glog/logging.h"
#include <fcntl.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>

namespace cetty {

Acceptor::Acceptor(EventLoop *loop, int port, IAcceptorCallback *callback)
    : port_(port), listenFd_(-1), serverSockChannel_(nullptr),
      callback_(callback), loop_(loop) {
  LOG(ERROR) << "Construct Acceptor:" << this;
}

Acceptor::~Acceptor() { LOG(ERROR) << "Destruct Acceptor:" << this; }

void Acceptor::start() {
  LOG(ERROR) << "Acceptor:" << this << " start";
  listenFd_ = listenOn();
  serverSockChannel_ = new Channel(loop_, listenFd_, this);
  serverSockChannel_->enableReading();
  LOG(ERROR) << "Acceptor:" << this << "is managed by EventLoop";
}

void Acceptor::handleRead() {
  int connFd;
  struct sockaddr_in cliAddr;
  socklen_t cliLen = sizeof(struct sockaddr_in);
  connFd = accept(listenFd_, (sockaddr *)&cliAddr, (socklen_t *)&cliLen);
  fcntl(connFd, F_SETFL, O_NONBLOCK);
  callback_->handleNewConnection(connFd);
}

void Acceptor::handleWrite() {}

// listenOn will listen to a port, and return the fd.
int Acceptor::listenOn() {
  int on = 1;
  listenFd_ = socket(AF_INET, SOCK_STREAM, 0);
  struct sockaddr_in serverAddr;
  fcntl(listenFd_, F_SETFL, O_NONBLOCK);
  setsockopt(listenFd_, SOL_SOCKET, SO_REUSEADDR, &on, sizeof on);
  serverAddr.sin_family = AF_INET;
  serverAddr.sin_addr.s_addr = htonl(0x7f000001);
  serverAddr.sin_port = htons(port_);
  if (-1 ==
      bind(listenFd_, (struct sockaddr *)&serverAddr, sizeof serverAddr)) {
  }
  LOG(ERROR) << "Acceptor::listenOn bind successfully";
  if (-1 == listen(listenFd_, 5)) {
  }
  LOG(ERROR) << "Acceptor::listenOn listen successfully";
  return listenFd_;
}
} // namespace cetty