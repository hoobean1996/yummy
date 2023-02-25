#include "cc/src/cetty/client.h"
#include "src/cetty/channel.h"
#include "src/cetty/event_loop.h"
#include <chrono>
#include <glog/logging.h>
#include <iomanip>
#include <sstream>
#include <sys/socket.h>

class ClientConnectionCallback : public cetty::IConnectionCallback {
public:
  ClientConnectionCallback() {}
  ~ClientConnectionCallback() {}
  std::string now() {
    auto now = std::chrono::system_clock::now();
    std::time_t time = std::chrono::system_clock::to_time_t(now);
    std::tm tm_time = *std::localtime(&time);
    std::ostringstream oss;
    oss << std::put_time(&tm_time, "%Y-%m-%d %H:%M:%S");
    return oss.str();
  }
  void onConnection(cetty::Connection *c) override {
    LOG(ERROR) << "Client connection is ready";
  }
  void onMessage(cetty::Connection *conn, common::Buffer *message) override {
    LOG(ERROR) << "Client recv " << message->readAsString();
  }
  void onWriteComplete(cetty::Connection *) override {}
};

int main(int argc, char *argv[]) {
  google::InitGoogleLogging(argv[0]);
  cetty::EventLoop loop;
  cetty::Client client{&loop, new ClientConnectionCallback()};
  client.connect("127.0.0.1", 8001);
  loop.loop();
  return 0;
}