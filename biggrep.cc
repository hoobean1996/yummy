#include <iostream>
#include <string>
#include <vector>

#include "glog/logging.h"
#include "src/core/core.h"
#include <netdb.h>

int main(int argc, char *argv[]) {
  yummy::initYummy(argc, argv);
  struct hostent *ret = gethostbyname("www.google.com");
  LOG(ERROR) << ret->h_addr_list[0];
  return 0;
}