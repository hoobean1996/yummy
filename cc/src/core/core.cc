#include "core.h"
#include "gflags/gflags.h"
#include "glog/logging.h"
namespace yummy {
void initYummy(int argc, char **argv) {
  google::InitGoogleLogging(argv[0]);
  gflags::ParseCommandLineFlags(&argc, &argv, true);
  LOG(ERROR) << "init yummy";
}
} // namespace yummy