#pragma once

#include "event_handler.h"

const int kNew = -1;
const int kAdded = 1;
const int kDeleted = 2;

namespace cetty {
class EventLoop;

// @ezdoc
// Channel is used to manage a fd and its corresponding event handler.
class Channel {
public:
  Channel() = delete;
  Channel(EventLoop *loop, int fd, EventHandler *handler);
  ~Channel();

  void setReadyEvents(int revents);
  // setFlag is used to update the channel's status.
  void setFlag(int flag);
  // handleEvent when anything is aready, will trigger it.
  void handleEvent();
  void enableReading();
  void enableWriting();
  void enableAll();
  void disableWriting();
  bool isWriting();
  int getEvents();
  int getFd();
  int getFlag();

private:
  int fd_;
  int interestedEvents_;
  int readyEvents_;
  int flag_;

  EventHandler *handler_;
  EventLoop *loop_;

  void update();
};
} // namespace cetty