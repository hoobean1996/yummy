#pragma once

#include "buffer.h"
#include "channel.h"
#include <netinet/in.h>
#include <string>
#include <vector>

namespace cetty {

class Connection;

class IConnectionCallback {
public:
  virtual void onConnection(Connection *) = 0;
  virtual void onMessage(Connection *, common::Buffer *) = 0;
  virtual void onWriteComplete(Connection *) = 0;
};

class Connection : public EventHandler {
public:
  Connection(int sockFd, EventLoop *loop, IConnectionCallback *callback);
  ~Connection();

  using bytes = std::vector<char>;
  void send(bytes data);
  void sendMessage(const std::string &message);
  void sendInLoop(const std::string &message);
  void connectionEstablished();

  virtual void handleReadEvent();
  virtual void handleWriteEvent();

private:
  int sockFd_;
  Channel *sockChannel_;
  EventLoop *loop_;
  IConnectionCallback *app_;
  common::Buffer *outBuffer_;
  common::Buffer *inBuffer_;
};
} // namespace cetty