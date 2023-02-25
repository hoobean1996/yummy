#include "client.h"
#include "cc/src/cetty/channel.h"
#include "cc/src/cetty/connection.h"
#include <arpa/inet.h>
#include <asm-generic/errno-base.h>
#include <asm-generic/errno.h>
#include <cerrno>
#include <cstring>
#include <fcntl.h>
#include <netinet/in.h>
#include <sys/epoll.h>
#include <sys/socket.h>

namespace cetty {
Client::Client(EventLoop *loop, IConnectionCallback *callback)
    : loop_(loop), callback_(callback), channel_(nullptr), sockFd_(-1) {
  LOG(ERROR) << "Construct Client: " << this;
}
Client::~Client() { LOG(ERROR) << "Descruct Client: " << this; }

void Client::handleReadEvent() {
  LOG(ERROR) << "ClientChannelCallback - handleRead";
};
void Client::handleWriteEvent() {
  LOG(ERROR) << "connect to server successfully";
  channel_->setFlag(kDeleted);
  channel_->disableWriting();
  LOG(ERROR) << "create new connection in handleWriteEvent";
  connection_ = new Connection(sockFd_, loop_, callback_);
  connection_->connectionEstablished();
  callback_->onConnection(connection_);
};

// Nonblocking connect
// 1. create socket
// 2. fcntl
// 3. connect
// 4. check connect result
//  0 => successfully
//  -1 + errno == EINPROGRESS, use epoll wait
void Client::connect(std::string ip, int port) {
  sockFd_ = socket(AF_INET, SOCK_STREAM, 0);
  if (sockFd_ < 0) {
    LOG(FATAL) << "Create socket failed";
  }
  // set as non-blocking
  fcntl(sockFd_, F_SETFL, O_NONBLOCK);

  struct sockaddr_in server_addr;
  std::memset(&server_addr, 0, sizeof(server_addr));

  server_addr.sin_family = AF_INET;
  server_addr.sin_addr.s_addr = ::inet_addr(ip.c_str());
  server_addr.sin_port = htons(port);

  int ret =
      ::connect(sockFd_, (struct sockaddr *)&server_addr, sizeof(server_addr));
  if (ret == 0) {
    LOG(ERROR) << "fast create connection";
    connection_ = new Connection(sockFd_, loop_, callback_);
    connection_->connectionEstablished();
    callback_->onConnection(connection_);
  } else if (ret == -1) {
    if (errno != EINPROGRESS) {
      close(sockFd_);
      LOG(FATAL) << "connect to server failed";
    } else {
      channel_ = new Channel(loop_, sockFd_, this);
      channel_->enableWriting();
    }
  }
}

} // namespace cetty