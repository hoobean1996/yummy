#include "event_loop.h"
#include "glog/logging.h"

namespace cetty {

EventLoop::EventLoop() : running_(true), poller_(new Poller()) {
  LOG(ERROR) << "Construct EventLoop:" << this;
}

EventLoop::~EventLoop() { LOG(ERROR) << "Desctruct EventLoop:" << this; }

void EventLoop::loop() {
  LOG(ERROR) << "EventLoop:" << this << " is polling";
  while (running_) {
    std::vector<Channel *> channels;
    poller_->poll(&channels);
    for (auto it = channels.begin(); it != channels.end(); it++) {
      (*it)->handleEvent();
    }
  }
}

void EventLoop::update(Channel *channel) { poller_->update(channel); }
} // namespace cetty