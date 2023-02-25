#include "addr.h"

namespace cetty {
Addr::Addr(std::string ip, int port) : ip_(ip), port_(port) {}
Addr::~Addr() {}
std::string Addr::getIP() const { return ip_; }
int Addr::getPort() const { return port_; }
} // namespace cetty