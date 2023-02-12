#include "core.h"
#include "glog/logging.h"
namespace yummy {
void initYummy(int argc, char **argv) {
  google::InitGoogleLogging(argv[0]);
  LOG(ERROR) << "init yummy";
}
} // namespace yummy