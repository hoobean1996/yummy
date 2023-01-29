#include "dialer.h"
#include "channel.h"
#include "glog/logging.h"
#include <asm-generic/errno-base.h>
#include <asm-generic/errno.h>
#include <cerrno>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>

namespace cetty {
Dialer::Dialer(EventLoop *loop, struct sockaddr_in addr,
               IDialerCallback *callback)
    : loop_(loop), addr_(addr), callback_(callback), channel_(nullptr) {
  LOG(ERROR) << "Construct Dialer:" << this;
}

Dialer::~Dialer() { LOG(ERROR) << "Destruct Dialer:" << this; }

void Dialer::handleRead() {}
void Dialer::handleWrite() {}

void Dialer::connecting(int sockFd) {
  this->setState(kConnecting);
  channel_ = new Channel(loop_, sockFd, this);
  channel_->enableWriting();
}

void Dialer::retry(int sockFd) {
  ::close(sockFd);
  setState(kDisconnected);
}

void Dialer::connect() {
  int sockFd = ::socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
  if (sockFd) {
    LOG(FATAL) << "Dialer::connect failed";
  }
  int ret = ::connect(sockFd, (struct sockaddr *)(&addr_),
                      static_cast<socklen_t>(sizeof(struct sockaddr_in)));
  int savedErrorNumber = (ret == 0) ? 0 : errno;
  switch (savedErrorNumber) {
  case 0:
  case EINPROGRESS:
  case EINTR:
  case EISCONN:
    connecting(sockFd);
    break;

  case EAGAIN:
  case EADDRINUSE:
  case EADDRNOTAVAIL:
  case ECONNREFUSED:
  case ENETUNREACH:
    retry(sockFd);
    break;

  case EACCES:
  case EPERM:
  case EAFNOSUPPORT:
  case EALREADY:
  case EBADF:
  case EFAULT:
  case ENOTSOCK:
    LOG(FATAL) << "Dialer::connect fatal, errno=" << savedErrorNumber;
    ::close(sockFd);
    break;
  default:
    LOG(FATAL) << "Dialer::connect unexpected status, errno="
               << savedErrorNumber;
    ::close(sockFd);
    break;
  }
}
} // namespace cetty