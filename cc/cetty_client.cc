#include "cc/src/cetty/client.h"
#include "src/cetty/channel.h"
#include "src/cetty/event_loop.h"
#include <glog/logging.h>
#include <sys/socket.h>

class ClientConnectionCallback : public cetty::IConnectionCallback {
public:
  ClientConnectionCallback() {
    LOG(ERROR) << "Construct ClientConnectionCallback:" << this;
  }
  ~ClientConnectionCallback() {
    LOG(ERROR) << "Destruct ClientConnectionCallback:" << this;
  }
  void onConnection(cetty::Connection *c) override {
    LOG(ERROR) << "ClientConnectionCallback:" << this << " onConnection";
    c->sendMessage("hello world");
  }
  void onMessage(cetty::Connection *conn, common::Buffer *message) override {
    LOG(ERROR) << "ClientConnectionCallback:" << this << " onMessage";
    LOG(ERROR) << "message = " << message->readAsString();
  }
  void onWriteComplete(cetty::Connection *) override {
    LOG(ERROR) << "ClientConnectionCallback:" << this << " onWriteComplete";
  }
};

int main(int argc, char *argv[]) {
  google::InitGoogleLogging(argv[0]);
  cetty::EventLoop loop;
  cetty::Client client{&loop, new ClientConnectionCallback()};
  client.blockingConnect("127.0.0.1", 8889);
  loop.loop();
  return 0;
}