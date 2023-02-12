#include "co.h"

#include "glog/logging.h"
#include <assert.h>
#include <cstring>
#include <ucontext.h>
#include <unistd.h>
#include <vector>

static void mainfunc(uint32_t low32, uint32_t hi32) {
  uintptr_t ptr = (uintptr_t)low32 | ((uintptr_t)hi32 << 32);
  Scheduler *s = reinterpret_cast<Scheduler *>(ptr);
  int id = s->running();
  Coroutine *co = s->getCoroutine(id);
  co->func()(s, co->ud());
  co->getScheduler()->stop(co);
}

Scheduler *Coroutine::getScheduler() { return scheduler_; }

Coroutine::Coroutine(Scheduler *s, CoroutineFunc func, void *ud)
    : func_(func), ud_(ud), scheduler_(s), cap_(0), size_(0), status_(kReady),
      stack_(nullptr) {
  LOG(ERROR) << "Construct Coroutine:" << this;
}

Coroutine::~Coroutine() { LOG(ERROR) << "Destruct Coroutine:" << this; }

// ***** Scheduler
Scheduler::Scheduler()
    : nco_(0), cap_(kDefaultCoroutine), running_(-1),
      co_(std::vector<Coroutine *>(kDefaultCoroutine)) {
  LOG(ERROR) << "Construct Scheduler:" << this << "\n"
             << "\t"
             << "nco=" << nco_ << "\n"
             << "\t"
             << "cap=" << cap_ << "\n"
             << "\t"
             << "running=" << running_ << "\n";
}

void Scheduler::stop(Coroutine *co) {
  for (int i = 0; i < cap_; i++) {
    if (co_[i] == co) {
      co_[i]->~Coroutine();
      co_[i] = nullptr;
      nco_--;
      running_ = -1;
      return;
    }
  }
}

int Scheduler::start(Coroutine *co) {
  LOG(ERROR) << "start Coroutine:" << co;
  if (nco_ > cap_) {
    int id = cap_;
    co_.resize(2 * cap_);
    co_[id] = co;
    nco_++;
    LOG(ERROR) << "place coroutine in " << id;
    return id;
  }
  for (int i = 0; i < cap_; i++) {
    if (co_[i] == nullptr) {
      co_[i] = co;
      nco_++;
      LOG(ERROR) << "place coroutine in " << i;
      return i;
    }
  }
  return 0;
}

void Scheduler::yield() {
  sleep(1);
  int id = running_;
  Coroutine *co = co_[id];
  saveStack(co, stack_ + kStackSize);
  co->status_ = kSuspend;
  running_ = -1;
  LOG(ERROR) << "Yield: Coroutine:" << co;
  swapcontext(&co->ctx_, &main_);
}

void Scheduler::saveStack(Coroutine *co, char *top) {
  char dummy = 0;
  // 在Linux中，栈是从高地址像低地址扩展
  // 所以stack_ + kStackSize => 栈底
  // dummy 此时在栈中，肯定是最低位置 => 栈顶
  // top - &dummy => 栈容量
  if (co->cap_ < top - &dummy) {
    delete co->stack_;
    co->cap_ = top - &dummy;
    co->stack_ = new char[co->cap_];
  }
  co->size_ = top - &dummy;
  memcpy(co->stack_, &dummy, co->size_);
}

void Scheduler::resume(int id) {
  sleep(1);
  auto co = co_[id];
  if (co == nullptr) {
    return;
  }
  auto status = co->status_;
  LOG(ERROR) << "Resume Coroutine:" << co
             << " status=" << CoroutineStatusNames[status];
  switch (status) {
  case kReady: {
    getcontext(&co->ctx_);
    co->ctx_.uc_stack.ss_sp = stack_;
    co->ctx_.uc_stack.ss_size = kStackSize;
    co->ctx_.uc_link = &main_;
    running_ = id;
    co->status_ = kRunning;
    uintptr_t ptr = (uintptr_t)this;
    makecontext(&co->ctx_, (void (*)(void))mainfunc, 2, (uint32_t)ptr,
                (uint32_t)(ptr >> 32));
    swapcontext(&main_, &co->ctx_);
    break;
  }
  case kSuspend: {
    memcpy(stack_ + kStackSize - co->size_, co->stack_, co->size_);
    running_ = id;
    co->status_ = kRunning;
    swapcontext(&main_, &co->ctx_);
    break;
  }
  default: {
    assert(0);
  }
  }
}

CoroutineFunc Coroutine::func() { return func_; }

Coroutine *Scheduler::getCoroutine(int id) { return co_[id]; }

void *Coroutine::ud() { return ud_; }

int Scheduler::running() { return running_; }

CoroutineStatus Scheduler::getStatus(int id) {
  if (co_[id] == nullptr) {
    return kDead;
  }
  return co_[id]->status_;
}

void Scheduler::shutdown() {
  for (int i = 0; i < cap_; i++) {
    auto co = co_[i];
    if (co) {
      co->~Coroutine();
    }
  }
}

Scheduler::~Scheduler() { LOG(ERROR) << "Destruct Scheduler:" << this; }