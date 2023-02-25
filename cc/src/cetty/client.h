#pragma once

#include "cc/src/cetty/channel.h"
#include "cc/src/cetty/connection.h"
#include "glog/logging.h"
#include <sys/epoll.h>
namespace cetty {
class Client {
public:
  Client(EventLoop *loop, IConnectionCallback *callback);
  ~Client();

  void connect(std::string ip, int port);
  void connect(int port);

private:
  struct epoll_event events_[1024];
  Connection *connection_;
  EventLoop *loop_;
  IConnectionCallback *callback_;
};
} // namespace cetty