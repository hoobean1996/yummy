#include <string>

#include "buffer.h"

namespace common {
Buffer::Buffer() {}
Buffer::Buffer(const std::string &data) : buf_(data) {}
Buffer::~Buffer() {}
void Buffer::retrieve(int n) { buf_ = buf_.substr(n, buf_.size()); }
const char *Buffer::peek() { return buf_.c_str(); }
int Buffer::readableBytes() { return static_cast<int>(buf_.size()); }
std::string Buffer::readAsString() {
  std::string result(peek(), readableBytes());
  buf_ = buf_.substr(readableBytes(), buf_.size());
  return result;
}
void Buffer::writeString(const std::string &buf) { buf_.append(buf); }
} // namespace common