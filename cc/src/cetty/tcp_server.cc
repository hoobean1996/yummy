#include "tcp_server.h"
#include "cc/src/cetty/channel.h"
#include "cc/src/cetty/connection.h"
#include "cc/src/cetty/server.h"
#include <ostream>

namespace cetty {
TCPServer::TCPServer(EventLoop *loop)
    : Server(loop, new ServerConnectionCallback()) {
  LOG(ERROR) << "Construct TPCServer: " << this << std::endl;
}

TCPServer::~TCPServer() {
  LOG(ERROR) << "Destruct TCPServer: " << this << std::endl;
}
} // namespace cetty