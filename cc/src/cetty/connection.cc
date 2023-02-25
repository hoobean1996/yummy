#include <glog/logging.h>

#include "buffer.h"
#include "channel.h"
#include "connection.h"

namespace cetty {
Connection::Connection(int sockFd, EventLoop *loop,
                       IConnectionCallback *callback)
    : sockFd_(sockFd), loop_(loop), app_(callback),
      outBuffer_(new common::Buffer()) {
  LOG(ERROR) << "Construct Connection:" << this << " fd=" << sockFd;
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
  LOG(ERROR) << "Connection:" << this << " Connection::handleRead";
  int sockFd = sockChannel_->getFd();
  int readLength;
  char line[1024];
  if (sockFd < 0) {
    return;
  }
  bzero(line, 1024);
  if ((readLength = read(sockFd, line, 1024)) < 0) {
    if (errno == ECONNRESET) {
      close(sockFd);
    }
  } else if (readLength == 0) {
    close(sockFd);
  } else {
    std::string lineStr(line, readLength);
    common::Buffer *buffer = new common::Buffer();
    buffer->writeString(lineStr);
    app_->onMessage(this, buffer);
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