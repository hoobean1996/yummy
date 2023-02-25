#pragma once

#include <map>
#include <sys/epoll.h>

#include "acceptor.h"
#include "addr.h"
#include "connection.h"
#include "event_loop.h"

namespace cetty {

// @ezdoc
// Server is the base class for all kinds of server.
// ::start(int port) will listen on given port in localhost.
class Server : public IAcceptorCallback {
public:
  Server(EventLoop *loop, IConnectionCallback *callback);
  ~Server();

  void start(std::string ip, int port);
  void start(int port);

  virtual void handleNewConnection(int sockFd);

private:
  struct epoll_event events_[1024];
  std::map<int, Connection *> connections_;
  Acceptor *acceptor_;
  EventLoop *loop_;
  IConnectionCallback *callback_;
};

} // namespace cetty
