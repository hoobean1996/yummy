#include "client.h"
#include "cc/src/cetty/channel.h"
#include "cc/src/cetty/connection.h"
#include <arpa/inet.h>
#include <cstring>
#include <fcntl.h>
#include <netinet/in.h>
#include <sys/socket.h>

namespace cetty {
Client::Client(EventLoop *loop, IConnectionCallback *callback)
    : loop_(loop), callback_(callback) {
  LOG(ERROR) << "Construct Client: " << this;
}
Client::~Client() { LOG(ERROR) << "Descruct Client: " << this; }

void Client::connect(std::string ip, int port) {
  int sockFd = socket(AF_INET, SOCK_STREAM, 0);
  if (sockFd < 0) {
    LOG(FATAL) << "Create socket failed";
  }

  struct sockaddr_in server_addr;
  std::memset(&server_addr, 0, sizeof(server_addr));
  server_addr.sin_family = AF_INET;
  server_addr.sin_addr.s_addr = ::inet_addr(ip.c_str());
  server_addr.sin_port = htons(port);

  if (::connect(sockFd, (struct sockaddr *)&server_addr, sizeof(server_addr)) <
      0) {
    LOG(FATAL) << "failed to connect to server";
  }

  fcntl(sockFd, F_SETFL, O_NONBLOCK);
  connection_ = new Connection(sockFd, loop_, callback_);
  connection_->connectionEstablished();
  LOG(ERROR) << "Construct Client Connection";
}

} // namespace cetty