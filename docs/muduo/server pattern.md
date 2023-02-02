# common patterns
Single Thread
1. Reactor模式: non-blocking IO + IO multiplexing 
   1. lighttpd
   2. libevent
   3. netty
2. Proactor:
   1. Boost.Asio


## Reactor
```c++
while (true) {
  int timeout = max(...);
  int retval = ::poll(...);
  if (retval < 0>) {
    handle error
  } else {
    handle timer
    handle IO event handler
  }
}
```
基于事件驱动的编程模型要求时间回调函数必须是非阻塞的。对于网络IO的请求响应式协议，容易割裂业务逻辑，使其分散在各个回调函数之中。

Multiple Thread:
1. One Request -> One Thread
2. Thread Pool
3. Non-Blocking I/O + Multiplexing (one loop per thread) + thread pool
   1. 线程数目固定
   2. 方便调整负载
   3. IO事件发生的线程时固定的，同一个TCP连接不必考虑事件并发。