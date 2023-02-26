syscall:
syscall(2) 列出所有的系统调用
- syscall 会将CPU从用户态切换到核心态
- syscall 是固定的，由唯一的数字标识
- syscall 的参数传递是固定的

int 0x80, sysenter指令都能触发中断

system_call 进行响应：
- save registers
- check
- syscall
- restore registers
- return

getpid: 10 million ~= 2.2s
getNumber: 10 million ~= 0.11s

glibc, uClibc, dietlibc分别是服务器领域，嵌入式设备，以及受限内存条件下的c函数库

1. 查看服务器的libc版本
/lib/libc.so.6 可以获取版本信息, 
2. 查看应用程序二进制中的libc版本
ldd
3. 在代码中查看libc的版本
  __GLLIBC__
  __GLIBC_MINOR__

  ```c++
  #include <gnu/libc-version.h>

  const char *gnu_get_lic_version(void);
  ```

handle syscall error:
在系统调用失败的时候，会将全局整型变量errno设置为一个正数，来标识具体的错误。需要包含erron.h头文件
```c++
#include <errno.h>
```
如果syscall成功，errno绝对不会被重置为0，所以可能是之前的调用失败导致的。所以需要先检查函数的返回值是否表面出错，然后在进行errno确定错误原因。

```c++
#include <stdio.h>

// 打印msg所指的字符串，同时加上errno代表的错误消息
void perror(const char *msg);

#include <string.h>

char *strerror(int errno);
```
perror 和strerror都是环境敏感的语言(locale-sensitive)

lib/ename.c.inc 包含了所有的错误定义

可移植性问题:
特性测试宏: 通过测试应用程序的宏定义，来决定哪些可见。

标准系统数据类型中大多数，都以_t结尾。许多在<sys/types.h>中

blkcnt_t 文件块数量
blksize_t 文件块大小
cc_t 终端特殊字符
clock_t 系统时间
dev_t 设备号
DIR 目录流
fd_set fd集合

打印pid
```c++

printf("My PID is %ld \n", pid);

```