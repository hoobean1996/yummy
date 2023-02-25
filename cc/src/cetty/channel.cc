#include "cc/src/cetty/event_handler.h"
#include "glog/logging.h"
#include <sys/epoll.h>

#include "channel.h"
#include "event_loop.h"

namespace cetty {
Channel::Channel(EventLoop *loop, int fd, EventHandler *event_handler)
    : fd_(fd), interestedEvents_(0), readyEvents_(0), flag_(kNew),
      handler_(event_handler), loop_(loop) {}
Channel::~Channel() {}
void Channel::setReadyEvents(int revents) { readyEvents_ = revents; }
void Channel::setFlag(int flag) { flag_ = flag; }
void Channel::handleEvent() {
  if (readyEvents_ & EPOLLIN) {
    handler_->handleReadEvent();
  }
  if (readyEvents_ & EPOLLOUT) {
    handler_->handleWriteEvent();
  }
}
void Channel::update() { loop_->update(this); }
void Channel::enableReading() {
  interestedEvents_ |= EPOLLIN;
  update();
}
void Channel::enableWriting() {
  interestedEvents_ |= EPOLLOUT;
  update();
}
void Channel::enableAll() {
  interestedEvents_ |= EPOLLIN | EPOLLOUT | EPOLLET;
  update();
}
void Channel::disableWriting() {
  interestedEvents_ &= ~EPOLLOUT;
  update();
}
bool Channel::isWriting() { return readyEvents_ & EPOLLOUT; }
int Channel::getEvents() { return interestedEvents_; }
int Channel::getFd() { return fd_; }
int Channel::getFlag() { return flag_; }

} // namespace cetty