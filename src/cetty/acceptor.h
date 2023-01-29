#pragma once

#include "channel.h"
namespace cetty {
class IAcceptorCallback {
public:
  virtual void handleNewConnection(int fd) = 0;
};

class Acceptor : public IChannelCallback {
public:
  Acceptor(EventLoop *loop, int port, IAcceptorCallback *callback);
  ~Acceptor();
  void start();

  virtual void handleRead();
  virtual void handleWrite();

private:
  int port_;
  int listenFd_;
  Channel *serverSockChannel_;
  IAcceptorCallback *callback_;
  EventLoop *loop_;

  int listenOn();
};

} // namespace cetty