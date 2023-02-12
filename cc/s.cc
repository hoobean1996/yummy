#include <iostream>
#include <thread>

void fn() { std::cout << "hello fn" << std::endl; }

class BackgroundTask {
public:
  void operator()() const { std::cout << "background task" << std::endl; }
};

class ThreadGuard {
public:
  explicit ThreadGuard(std::thread &t) : t_(t) {}
  ~ThreadGuard() {
    if (t_.joinable()) {
      t_.join();
    }
  }

private:
  std::thread &t_;
};

int main() {
  std::cout << "hello world" << std::endl;
  std::thread t(fn);
  BackgroundTask fn2;
  std::thread t2(fn2);
  t.join();
  t2.join();
  std::thread t3([]() { std::cout << "fn3" << std ::endl; });

  std::cout << std::thread::hardware_concurrency() << std::endl;
  return 0;
}