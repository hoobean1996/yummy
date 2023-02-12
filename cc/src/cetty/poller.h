#pragma once

#include <sys/epoll.h>
#include <vector>

namespace cetty {
class Channel;

class Poller {
public:
  Poller();
  ~Poller();

  void poll(std::vector<Channel *> *channels);

  void update(Channel *channel);

private:
  static const int kMaxEvents_ = 1024;
  int epollFd_;
  struct epoll_event events_[kMaxEvents_];
};
} // namespace cetty