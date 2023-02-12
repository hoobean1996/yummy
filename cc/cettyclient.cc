#include "src/cetty/channel.h"
#include "src/cetty/dialer.h"
#include "src/cetty/event_loop.h"
#include <glog/logging.h>
#include <sys/socket.h>

class DialerCallback : public cetty::IDialerCallback {
public:
  void onConnectionEstablished(int fd) override {
    LOG(ERROR) << "onConnection";
  }
};

int main(int argc, char *argv[]) {
  google::InitGoogleLogging(argv[0]);
  cetty::EventLoop loop;
  struct sockaddr_in serverAddr;
  serverAddr.sin_family = AF_INET;
  serverAddr.sin_port = 8888;
  serverAddr.sin_addr.s_addr = htonl(0x7f000001);
  cetty::Dialer dialer{&loop, serverAddr, new DialerCallback()};
  dialer.connect();
  return 0;
}