#pragma once

namespace cetty {
// EventHandler represents the handler which need to
// process the EPOLLIN, EPOLLOUT events.
class EventHandler {
public:
  virtual void handleReadEvent() = 0;
  virtual void handleWriteEvent() = 0;
};
} // namespace cetty