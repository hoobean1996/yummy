
#include "server.h"
#include "cc/src/cetty/acceptor.h"
#include "cc/src/cetty/addr.h"
#include "connection.h"
#include "glog/logging.h"

namespace cetty {
Server::Server(EventLoop *loop, IConnectionCallback *callback)
    : acceptor_(nullptr), loop_(loop), callback_(callback) {}

Server::~Server() {}

void Server::start(std::string ip, int port) {
  acceptor_ = new Acceptor(loop_, new Addr(ip, port), this);
  acceptor_->start();
}

void Server::start(int port) {
  acceptor_ = new Acceptor(loop_, new Addr("127.0.0.1", port), this);
  acceptor_->start();
}

void Server::handleNewConnection(int sockFd) {
  Connection *connection = new Connection(sockFd, loop_, callback_);
  connections_[sockFd] = connection;
  connection->connectionEstablished();
}
} // namespace cetty