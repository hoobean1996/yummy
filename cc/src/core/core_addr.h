#pragma once

#include <cstdint>
#include <string>
namespace yummy {
namespace core {
enum class AddrType {
  IPv4,
  IPv6,
};

struct Addr {
public:
  virtual AddrType kind() = 0;
  virtual std::string network() = 0;
  virtual std::string toString() = 0;
};

struct IPv4Addr : public Addr {
public:
  AddrType kind() { return AddrType::IPv4; }
  std::string network() { int32_t net = addr_ & mask_; }

private:
  std::int32_t addr_;
  std::int32_t mask_;
};
} // namespace core
}; // namespace yummy