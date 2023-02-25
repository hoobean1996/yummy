#include "client.h"
#include "cc/src/cetty/channel.h"
#include "cc/src/cetty/connection.h"
#include <arpa/inet.h>
#include <cerrno>
#include <cstring>
#include <fcntl.h>
#include <netinet/in.h>
#include <sys/socket.h>

namespace cetty {
Client::Client(EventLoop *loop, IConnectionCallback *callback)
    : loop_(loop), callback_(callback), channel_(nullptr), sockFd_(-1) {
  LOG(ERROR) << "Construct Client: " << this;
}
Client::~Client() { LOG(ERROR) << "Descruct Client: " << this; }

void Client::handleReadEvent() {
  LOG(ERROR) << "ClientChannelCallback - handleRead";
};
void Client::handleWriteEvent() {
  LOG(ERROR) << "CllientChannelCallback - handleWrite";
  connection_ = new Connection(sockFd_, loop_, callback_);
  connection_->connectionEstablished();
  callback_->onConnection(connection_);
};

void Client::blockingConnect(std::string ip, int port) {
  int sockFd = socket(AF_INET, SOCK_STREAM, 0);
  if (sockFd < 0) {
    LOG(FATAL) << "Create socket failed";
  }
  struct sockaddr_in server_addr;
  std::memset(&server_addr, 0, sizeof(server_addr));
  server_addr.sin_family = AF_INET;
  server_addr.sin_addr.s_addr = ::inet_addr(ip.c_str());
  server_addr.sin_port = htons(port);
  LOG(ERROR) << "connect to " << ::inet_addr(ip.c_str()) << ", " << ip;
  int ret =
      ::connect(sockFd, (struct sockaddr *)&server_addr, sizeof(server_addr));
  int savedErrno = (ret == 0) ? 0 : errno;
  if (savedErrno) {
    LOG(ERROR) << "savedErrno=" << savedErrno;
  }
  connection_ = new Connection(sockFd_, loop_, callback_);
  connection_->connectionEstablished();
  callback_->onConnection(connection_);
}

void Client::connect(std::string ip, int port) {
  int sockFd = socket(AF_INET, SOCK_STREAM, 0);
  if (sockFd < 0) {
    LOG(FATAL) << "Create socket failed";
  }
  struct sockaddr_in server_addr;
  std::memset(&server_addr, 0, sizeof(server_addr));
  fcntl(sockFd, F_SETFL, O_NONBLOCK);
  server_addr.sin_family = AF_INET;
  server_addr.sin_addr.s_addr = ::inet_addr(ip.c_str());
  server_addr.sin_port = htons(port);
  int ret =
      ::connect(sockFd, (struct sockaddr *)&server_addr, sizeof(server_addr));
  int savedErrno = (ret == 0) ? 0 : errno;
  LOG(ERROR) << "savedErrno" << savedErrno;
  switch (savedErrno) {
  case 0:
  case EINPROGRESS:
  case EINTR:
  case EISCONN:
    channel_ = new Channel(loop_, sockFd, this);
    channel_->enableWriting();
    break;
  case EAGAIN:
  case EADDRINUSE:
  case EADDRNOTAVAIL:
  case ECONNREFUSED:
  case ENETUNREACH:
    // retry(sockFd);

  case EACCES:
  case EPERM:
  case EAFNOSUPPORT:
  case EALREADY:
  case EBADF:
  case EFAULT:
  case ENOTSOCK:
    LOG(FATAL) << "connect error in Connector::startInLoop " << savedErrno;
    break;

  default:
    LOG(FATAL) << "Unexpected error in Connector::startInLoop " << savedErrno;
    break;
  }
}

} // namespace cetty