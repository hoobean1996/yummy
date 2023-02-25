#pragma once

#include <string>

namespace cetty {
class Addr {
public:
  Addr(std::string ip, int port);
  ~Addr();
  std::string getIP() const;
  int getPort() const;

private:
  std::string ip_;
  int port_;
};
} // namespace cetty