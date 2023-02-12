#include "core_socket.h"
#include "core.h"
#include <sys/socket.h>

namespace yummy {
namespace net {
fd createSocket(int domain, int type, int protocol) {
  int fd_ = ::socket(domain, type, protocol);
  return fd{fd_};
}

fd createTCPSocket() { return createSocket(AF_INET, SOCK_STREAM, 0); }

} // namespace net
} // namespace yummy