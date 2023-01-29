#pragma once

#include "channel.h"
#include "poller.h"
namespace cetty {
class EventLoop {
public:
  EventLoop();
  ~EventLoop();

  void loop();
  void update(Channel *channel);

private:
  bool running_;
  Poller *poller_;
};
} // namespace cetty