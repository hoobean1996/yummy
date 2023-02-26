#include <cstring>
#include <fcntl.h>
#include <glog/logging.h>
#include <sys/stat.h>
#include <sys/types.h>

const int kBufSize = 1024;

int main(int argc, char *argv[]) {
  char buf[kBufSize];

  if (argc != 3 || strcmp(argv[1], "--help") == 0) {
    LOG(FATAL) << "copy old-file new-file";
  }

  int inputFd = open(argv[1], O_RDONLY);
  if (inputFd == -1) {
    LOG(ERROR) << strerror(errno);
    LOG(FATAL) << "open file failed " << argv[1];
  }
  int openFlags = O_CREAT | O_WRONLY | O_TRUNC;
  mode_t filePerms = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH;
  int outputFd = open(argv[2], openFlags, filePerms);
  if (outputFd == -1) {
    LOG(FATAL) << "open file failed " << argv[2];
  }
  int n;
  while ((n = read(inputFd, buf, kBufSize)) > 0) {
    if (write(outputFd, buf, n) != n) {
      LOG(FATAL) << "could not write whole buffer";
    }
  }
  if (n == -1) {
    LOG(FATAL) << "read failed";
  }
  close(inputFd);
  close(outputFd);
  return 0;
}