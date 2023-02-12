#include "glog/logging.h"
#include "src/co/co.h"
#include "src/core/core.h"
#include <unistd.h>
struct Arg {
  int n;
};

int main(int argc, char *argv[]) {
  yummy::initYummy(argc, argv);
  Scheduler s;

  Arg arg1 = {0};
  Arg arg2 = {100};

  Coroutine co1(
      &s,
      [](Scheduler *s, void *ud) {
        Arg *arugment = reinterpret_cast<Arg *>(ud);
        for (int i = 0; i < 5; i++) {
          LOG(ERROR) << "Co1:" << arugment->n + i;
          s->yield();
        }
        LOG(ERROR) << "Co1: end";
      },
      &arg1);
  Coroutine co2(
      &s,
      [](Scheduler *s, void *ud) {
        Arg *arugment = reinterpret_cast<Arg *>(ud);
        for (int i = 0; i < 5; i++) {
          LOG(ERROR) << "Co2:" << i + arugment->n;
          s->yield();
        }
        LOG(ERROR) << "Co2: end";
      },
      &arg2);
  int id1 = s.start(&co1);
  int id2 = s.start(&co2);

  while (s.getStatus(id1) && s.getStatus(id2)) {
    s.resume(id1);
    s.resume(id2);
  }
  LOG(ERROR) << "main coroutine end";
  sleep(5);
  s.shutdown();
  return 0;
}