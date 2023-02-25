
#include "server.h"
#include "cc/src/cetty/acceptor.h"
#include "cc/src/cetty/addr.h"
#include "connection.h"
#include "glog/logging.h"

namespace cetty {
Server::Server(EventLoop *loop, IConnectionCallback *callback)
    : acceptor_(nullptr), loop_(loop), callback_(callback) {
  LOG(ERROR) << "Construct Server:" << this;
}

Server::~Server() { LOG(ERROR) << "Destruct Server:" << this; }

void Server::start(std::string ip, int port) {
  LOG(ERROR) << "Server::start at ip:" << ip << ",port:" << port << std::endl;
  acceptor_ = new Acceptor(loop_, new Addr(ip, port), this);
  acceptor_->start();
}

void Server::start(int port) {
  LOG(ERROR) << "Server::start at port:" << port;
  acceptor_ = new Acceptor(loop_, new Addr("127.0.0.1", port), this);
  acceptor_->start();
}

void Server::handleNewConnection(int sockFd) {
  LOG(ERROR) << "Server::handleNewConnection fd=" << sockFd;
  Connection *connection = new Connection(sockFd, loop_, callback_);
  connections_[sockFd] = connection;
  connection->connectionEstablished();
  LOG(ERROR) << "Channel for fd=" << sockFd << " is managed by EventLoop";
}
} // namespace cetty