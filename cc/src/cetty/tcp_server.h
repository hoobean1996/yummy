#pragma once

#include "cc/src/cetty/channel.h"
#include "cc/src/cetty/server.h"
#include "glog/logging.h"

namespace cetty {

class ServerConnectionCallback : public cetty::IConnectionCallback {
public:
  ServerConnectionCallback() {}
  ~ServerConnectionCallback() {}
  void onConnection(cetty::Connection *) override {}
  void onMessage(cetty::Connection *conn, common::Buffer *message) override {
    LOG(ERROR) << "message = " << message->readAsString();
  }
  void onWriteComplete(cetty::Connection *) override {}
};

class TCPServer : public Server {
public:
  TCPServer(EventLoop *loop);
  ~TCPServer();
};
} // namespace cetty