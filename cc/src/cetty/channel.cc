#include "glog/logging.h"
#include <sys/epoll.h>

#include "channel.h"
#include "event_loop.h"

namespace cetty {
Channel::Channel() {}
Channel::Channel(EventLoop *loop, int fd, IChannelCallback *callback)
    : fd_(fd), events_(0), revents_(0), flag_(kNew), callback_(callback),
      loop_(loop) {
  LOG(ERROR) << "Construct Channel:" << this << " fd=" << fd;
}
Channel::~Channel() {}
void Channel::setRevents(int revents) { revents_ = revents; }
void Channel::setFlag(int flag) { flag_ = flag; }
void Channel::handleEvent() {
  if (revents_ & EPOLLIN) {
    LOG(ERROR) << "Channel:" << this << " EPOLLIN";
    callback_->handleRead();
  }
  if (revents_ & EPOLLOUT) {
    LOG(ERROR) << "Channel:" << this << " EPOLLOUT";
    callback_->handleWrite();
  }
}
void Channel::update() { loop_->update(this); }
void Channel::enableReading() {
  events_ |= EPOLLIN;
  update();
}
void Channel::enableWriting() {
  events_ |= EPOLLOUT;
  update();
}
void Channel::disableWriting() {
  events_ &= ~EPOLLOUT;
  update();
}
bool Channel::isWriting() { return events_ & EPOLLOUT; }
int Channel::getEvents() { return events_; }
int Channel::getFd() { return fd_; }
int Channel::getFlag() { return flag_; }

} // namespace cetty