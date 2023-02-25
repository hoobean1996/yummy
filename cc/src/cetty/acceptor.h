#pragma once

#include "addr.h"
#include "channel.h"
namespace cetty {
class IAcceptorCallback {
public:
  virtual void handleNewConnection(int fd) = 0;
};

// @ezdoc
// Acceptor is used to accept new connection.
// Server will embed the acceptor to listen on given IP:Port, so we provide a
// callback for Server to manage connections.
class Acceptor : public EventHandler {
public:
  Acceptor(EventLoop *loop, Addr *addr, IAcceptorCallback *callback);
  ~Acceptor();
  void start();

  void handleReadEvent() override;
  void handleWriteEvent() override;

private:
  int port_;
  int listenFd_;
  Addr *addr_;
  Channel *serverSockChannel_;
  IAcceptorCallback *callback_;
  EventLoop *loop_;

  int listenOn();
};

} // namespace cetty