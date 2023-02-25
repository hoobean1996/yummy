#pragma once

#include "cc/src/cetty/channel.h"
#include "cc/src/cetty/server.h"
#include "glog/logging.h"

namespace cetty {

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

class TCPServer : public Server {
public:
  TCPServer(EventLoop *loop);
  ~TCPServer();
};
} // namespace cetty