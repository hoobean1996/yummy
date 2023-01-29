#include "glog/logging.h"
#include "src/cetty/connection.h"
#include "src/cetty/event_loop.h"
#include "src/cetty/server.h"
#include "src/core/core.h"

class ServerConnectionCallback : public cetty::IConnectionCallback {
public:
  ServerConnectionCallback() {
    LOG(ERROR) << "Construct ServerConnectionCallback:" << this;
  }
  ~ServerConnectionCallback() {
    LOG(ERROR) << "Destruct ServerConnectionCallback:" << this;
  }
  void onConnection(cetty::Connection *) override {
    LOG(ERROR) << "ServerConnectionCallback:" << this << " onConnection";
  }
  void onMessage(cetty::Connection *conn, common::Buffer *message) override {
    LOG(ERROR) << "ServerConnectionCallback:" << this << " onMessage";
    LOG(ERROR) << "message = " << message->readAsString();
  }
  void onWriteComplete(cetty::Connection *) override {
    LOG(ERROR) << "ServerConnectionCallback:" << this << " onWriteComplete";
  }
};

int main(int argc, char *argv[]) {
  yummy::initYummy(argc, argv);
  cetty::EventLoop loop{};
  cetty::Server server{&loop, new ServerConnectionCallback()};
  server.start(8888);
  loop.loop();
  return 0;
}