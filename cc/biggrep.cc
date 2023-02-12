#include <iostream>
#include <string>
#include <vector>

#include "glog/logging.h"
#include "src/core/core.h"
#include <netdb.h>

int main(int argc, char *argv[]) {
  yummy::initYummy(argc, argv);
  return 0;
}