
#include <bits/types/struct_iovec.h>
#include <cstring>
#include <fcntl.h>
#include <glog/logging.h>
#include <sys/stat.h>
#include <sys/uio.h>
int main(int argc, char *argv[]) {
  if (argc != 2) {
    LOG(FATAL) << "readv file";
  }

  int fd = open(argv[1], O_RDONLY);
  if (fd == -1) {
    LOG(FATAL) << "open input file failed " << fd;
  }

  struct iovec iov[3];
  struct stat v1;
  int v2;
  char v3[100];

  int totRequired = 0;
  iov[0].iov_base = &v1;
  iov[0].iov_len = sizeof(struct stat);
  totRequired += iov[0].iov_len;

  iov[1].iov_base = &v2;
  iov[1].iov_len = sizeof(v2);
  totRequired += iov[1].iov_len;

  iov[2].iov_base = v3;
  iov[2].iov_len = 100;
  totRequired += iov[2].iov_len;

  int n = readv(fd, iov, 3);
  if (n == -1) {
    LOG(FATAL) << "readv failed " << strerror(errno);
  }
  if (n < totRequired) {
    LOG(FATAL) << "readv fewer than requested";
  }
  return 0;
}