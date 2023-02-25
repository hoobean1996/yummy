#include <cerrno>
#include <cstring>
#include <glog/logging.h>

#include "buffer.h"
#include "channel.h"
#include "connection.h"

namespace cetty {
Connection::Connection(int sockFd, EventLoop *loop,
                       IConnectionCallback *callback)
    : sockFd_(sockFd), loop_(loop), app_(callback),
      outBuffer_(new common::Buffer()), inBuffer_(new common::Buffer()) {
  sockChannel_ = new Channel(loop_, sockFd_, this);
  sockChannel_->enableReading();
  if (callback == nullptr) {
    sockChannel_->enableWriting();
  }
}

Connection::~Connection() {}

void Connection::send(bytes data) {}

void Connection::sendMessage(const std::string &message) {
  sendInLoop(message);
}

void Connection::sendInLoop(const std::string &message) {
  outBuffer_->writeString(message);
  if (!sockChannel_->isWriting()) {
    sockChannel_->enableWriting();
  }
}

void Connection::connectionEstablished() { app_->onConnection(this); }

void Connection::handleReadEvent() {
  int sockFd = sockChannel_->getFd();
  if (sockFd < 0) {
    return;
  }
  char line[1024];
  bzero(line, 1024);
  int readLength = read(sockFd, line, 1024);
  if (readLength < 0) {
    if (errno == ECONNRESET) {
      close(sockFd);
      LOG(FATAL) << "read failed, errno=" << errno
                 << ", errmsg=" << strerror(errno);
    }
  } else if (readLength == 0) {
    LOG(ERROR) << "readLength=0, remote close the connection";
    close(sockFd);
  } else {
    LOG(ERROR) << "readLength=" << readLength;
    std::string lineStr(line, readLength);
    inBuffer_->writeString(lineStr);
    app_->onMessage(this, inBuffer_);
  }
}

void Connection::handleWriteEvent() {
  int sockFd = sockChannel_->getFd();
  if (sockChannel_->isWriting()) {
    int n = ::write(sockFd, outBuffer_->peek(), outBuffer_->readableBytes());
    if (n > 0) {
      sockChannel_->disableWriting();
      outBuffer_->retrieve(n);
    }
  }
}

} // namespace cetty