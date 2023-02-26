
#include <cerrno>
#include <cstdio>
#include <cstring>
#include <fcntl.h>
#include <glog/logging.h>
#include <unistd.h>
int main(int argc, char *argv[]) {
  if (argc < 3) {
    LOG(FATAL) << "tee input output1 output2";
  }
  const char *inputFile = argv[1];
  int fd = open(inputFile, O_RDONLY);
  if (fd == -1) {
    LOG(FATAL) << "open input file failed " << strerror(errno);
  }
  for (int i = 2; i < argc; i++) {
    int openFlags = O_CREAT | O_WRONLY | O_TRUNC;
    mode_t filePerms =
        S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH;
    int outputFd = open(argv[i], openFlags, filePerms);
    if (outputFd == -1) {
      LOG(FATAL) << "open output file failed " << strerror(errno);
    }
    int n;
    char buf[1024];
    while ((n = read(fd, buf, 1024)) > 0) {
      if (write(outputFd, buf, n) != n) {
        LOG(FATAL) << "write to file failed";
      }
    }
    if (n == -1) {
      LOG(FATAL) << "read failed";
    }
    close(outputFd);
    lseek(fd, 0, SEEK_SET);
  }

  return 0;
}