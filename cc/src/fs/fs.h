#pragma once

#include <bits/stdint-intn.h>
#include <string>
class FileSystem {
public:
  FileSystem(std::string disk);
  ~FileSystem();

  int32_t createDirectory(std::string dir);

private:
  std::string disk_;
  // 4kb filesystem information
  // 4kb inode bitmap
  class SuperNode {};

  class INode {};

  const int blockSize = 4096;
};