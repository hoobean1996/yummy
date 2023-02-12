#pragma once

const int kNew = -1;
const int kAdded = 1;

class IChannelCallback {
public:
  virtual void handleRead() = 0;
  virtual void handleWrite() = 0;
};

namespace cetty {
class EventLoop;
class Channel {
public:
  Channel();
  Channel(EventLoop *loop, int fd, IChannelCallback *callback);
  ~Channel();

  void setRevents(int revents);
  void setFlag(int flag);
  // handleEvent when anything is aready, will trigger it.
  void handleEvent();
  void enableReading();
  void enableWriting();
  void disableWriting();
  bool isWriting();
  int getEvents();
  int getFd();
  int getFlag();

private:
  int fd_;
  int events_;
  int revents_;
  int flag_;
  IChannelCallback *callback_;
  EventLoop *loop_;
  void update();
};
} // namespace cetty