#pragma once

#include "cc/src/cetty/channel.h"
#include "cc/src/cetty/connection.h"
#include "cc/src/cetty/event_handler.h"
#include "glog/logging.h"
#include <sys/epoll.h>
namespace cetty {
class Client : public EventHandler {
public:
  Client(EventLoop *loop, IConnectionCallback *callback);
  ~Client();

  void connect(std::string ip, int port);
  void connect(int port);
  Connection *blockingConnect(std::string ip, int port);

  void handleReadEvent() override;
  void handleWriteEvent() override;

private:
  struct epoll_event events_[1024];
  Connection *connection_;
  EventLoop *loop_;
  IConnectionCallback *callback_;
  Channel *channel_;
  int sockFd_;
};
} // namespace cetty