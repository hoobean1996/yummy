#include "fs.h"
#include <cstring>
#include <fcntl.h>
#include <glog/logging.h>
#include <string.h>
#include <unistd.h>

FileSystem::FileSystem(std::string disk) : disk_(disk) {
  int diskFd = open(disk.c_str(), O_RDWR, 0666);
  if (diskFd == -1) {
    LOG(FATAL) << "open disk failed " << strerror(errno);
  }
  char metadata[blockSize];
  int n = read(diskFd, metadata, blockSize);
  if (n == 0) {
    LOG(FATAL) << "metadata block must not be null";
  }
  if (metadata[0] != 'v' && metadata[1] != 'f' && metadata[2] != 's') {
    LOG(ERROR) << "filesystem does not init";
  }
  char defaultMetadata[blockSize];
  memset(defaultMetadata, 0, blockSize);
  defaultMetadata[0] = 'v';
  defaultMetadata[1] = 'f';
  defaultMetadata[2] = 's';
  n = write(diskFd, defaultMetadata, blockSize);
  if (n != blockSize) {
    LOG(FATAL) << "filesystem init failed";
  }
  LOG(ERROR) << "filesystem init succeed";
}

int32_t FileSystem::createDirectory(std::string dir) { return 0; }

FileSystem::~FileSystem() {}