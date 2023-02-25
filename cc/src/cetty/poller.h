#pragma once

#include <sys/epoll.h>
#include <vector>

namespace cetty {
class Channel;

// @ezdoc
// Poller is used to illustrate epoll, poll and kqueue.
// Currently, we only support epoll.
class Poller {
public:
  Poller();
  ~Poller();
  // poll will extract ready evets from those fd, and store int channels.
  void poll(std::vector<Channel *> *channels);
  // update will use Channel's information to initialise epoll event.
  void update(Channel *channel);

private:
  int epollFd_;
  static const int maxEventsNum_ = 1024;
  struct epoll_event events_[maxEventsNum_];
};
} // namespace cetty