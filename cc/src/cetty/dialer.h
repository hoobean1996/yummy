#pragma once

#include "channel.h"
#include <netinet/in.h>
namespace cetty {
class IDialerCallback {
public:
  virtual void onConnectionEstablished(int fd) = 0;
};

class Dialer : public IChannelCallback {
public:
  Dialer(EventLoop *, sockaddr_in addr, IDialerCallback *callback);
  ~Dialer();
  void connect();

  enum States {
    kDisconnected,
    kConnecting,
    kConnected,
  };

  virtual void handleRead();
  virtual void handleWrite();

  void connecting(int sockFd);
  void retry(int sockFd);

private:
  void setState(States s) { state_ = s; }

  EventLoop *loop_;
  struct sockaddr_in addr_;
  IDialerCallback *callback_;
  States state_;
  Channel *channel_;
};
} // namespace cetty