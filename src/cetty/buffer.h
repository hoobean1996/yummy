#pragma once

#include <string>
namespace common {
class Buffer {
public:
  Buffer();
  Buffer(const std::string &data);
  ~Buffer();

  void retrieve(int n);
  const char *peek();
  int readableBytes();
  void writeString(const std::string &buf);
  std::string readAsString();

private:
  std::string buf_;
};
} // namespace common