#pragma once

#include <cstddef>
#include <functional>
#include <map>
#include <string>
#include <sys/ucontext.h>
#include <vector>
enum CoroutineStatus {
  kDead,
  kReady,
  kRunning,
  kSuspend,
};

static std::map<CoroutineStatus, std::string> CoroutineStatusNames = {
    {kDead, "dead"},
    {kReady, "read"},
    {kRunning, "running"},
    {kSuspend, "suspend"},
};

const int kStackSize = 1024 * 1024;
const int kDefaultCoroutine = 16;

class Coroutine;

class Scheduler {
  friend Coroutine;

public:
  Scheduler();
  ~Scheduler();

  int start(Coroutine *);
  void stop(Coroutine *);
  void yield();
  void resume(int id);
  void saveStack(Coroutine *, char *);
  void shutdown();
  int running();
  CoroutineStatus getStatus(int id);
  Coroutine *getCoroutine(int id);

private:
  // stack_ 运行时栈
  char stack_[kStackSize];
  // main_ 主协程的上下文
  ucontext_t main_;
  // nco_ 当前存活的协程个数
  int nco_;
  // cap_ 协程管理器的当前最大容量
  int cap_;
  // running 当前运行的协程ID
  int running_;
  // co_ 所有的协程
  std::vector<Coroutine *> co_;
};

using CoroutineFunc = std::function<void(Scheduler *, void *)>;

class Coroutine {
  friend Scheduler;

public:
  Coroutine(Scheduler *s, CoroutineFunc func, void *ud);
  ~Coroutine();

  CoroutineFunc func();
  void *ud();
  Scheduler *getScheduler();

private:
  CoroutineFunc func_;     // 协程使用的函数
  void *ud_;               // 协程运行的参数
  ucontext_t ctx_;         // 协程上下文
  Scheduler *scheduler_;   // 所属的调度器
  ptrdiff_t cap_;          // 分配的内存大小
  ptrdiff_t size_;         // 运行栈，保存以后的大小
  CoroutineStatus status_; //  当前协程的状态
  char *stack_;            // 协程保存起来的时候运行栈
};
