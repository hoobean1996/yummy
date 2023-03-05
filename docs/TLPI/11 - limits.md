一个进程能同时拥有多少已打开的文件？ 
系统是否支持实时信号？ 
int 类型变量可存储的最大值是多少？ 
一个程序的参数列表能有多大？ 
路径名的最大长度是多少？

在头文件 `limits.h`中能够找到
利用`getconf`也能轻松查找

```c++
// 在程序中获得限制值
long sysconf(int name); 

long pathconf(const char *pathname, int name);
long fpathconf(int fd, int name);
```