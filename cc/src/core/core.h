#pragma once
#include <netinet/in.h>
#include <string>
#include <sys/socket.h>

namespace yummy {
void initYummy(int argc, char *argv[]);

// fd is used to represents a file descriptor integer.
struct fd {
  int fd_;
};

struct addr {
  sa_family_t family_;
  in_port_t port_;
};

// error is used to presents a common error type, instead of a number.
struct error {
public:
  virtual std::string toString() = 0;
};
} // namespace yummy