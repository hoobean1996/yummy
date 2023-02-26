pid:
系统调用 getpid可以获得当前进程的pid
每个进程都有自己的父进程，所有利用系统调用 getppid来获得父进程的id，如果子进程的父进程终止，则子进程就会变成orphan进程，init进程立刻收养该进程。

layout:
text, data, stack, heap

利用size命令可以展示二进制可执行文件的结构

-----------------
|     kernel    |
-----------------
-----0xc0000000--
----argv, environment----

----stack base----
  stack grow down
----sp------------

unused memory

--------heap----
  heap grow up
--------heap----
  bss
  data
  text
....


vm:
虚拟内存的规划之一是将每个程序使用的内存分割成小型的、固定大小的页。将RAM划分为相同大小的页帧。
任何时刻，每个程序仅有部分page需要驻留在物理内存中，这些页构成了resident set。
程序未使用的page将会被拷贝保存在swap分区。
若进程需要访问的页面没有在物理内存中，会触发page fault，从而将对应的page调度。

虚拟内存的有点：
- 进程和进程之间相互隔离
- 进程和内核之间相互隔离
- 能够共享内存
- 实现内存保护机制
- 编译器、链接器无需关注程序在RAM中的物理布局

stack frame:
函数的调用和返回使得栈的增长和收缩呈线形。
专用寄存器sp用于跟踪当前的栈顶。
每次调用函数的时候，会在栈上新分配一个stack frame，当返回的时候，将stack frame移除。

每个栈帧包括以下信息：
- 函数的实参和局部变量
- 函数调用的链接信息：每个函数都用会到一些寄存器，在调用函数的时候，会在被调用函数的栈帧中保存寄存器的副本，从而使得被调用函数能够将寄存器恢复。


environment list:
每个进程都有一个与之相关的环境列表（字符串数组）。
每个字符串都是name=value的形式，在创建的时候，会继承父进程的环境副本。

可以利用全局变量 char **environ访问环境列表。
更好的的是利用getenv函数来从进程的环境中检索单个值。
```c++
char * getenv(const char *name);
int putenv(char *string);
int setenv(const char *name, const char *value, int override);
int unsetenv(const char *name);
int clearenv();
```

jmp:
使用库函数setjmp和longjmp可以执行非局部跳转。
goto只能在函数内部跳转，如果需要在深度嵌套的函数调用中发生了错误，需要放弃当前错误，从多层函数调用中返回，并在较高层中继续执行。
setjmp会后续的longjmp确定了跳转目标，该目标正是跳转的位置i。
```c++

int setjmp(jmp_buf env);
void longjmp(jmp_buf env, int val);
```
longjmp有两个关键步骤
1. 将发起longjmp调用的函数和之前调用setjmp的函数之间的函数栈帧从栈上剥离
2. 重置程序计数器


基于 setjmp 和 longjmp我们可以实现简单的异常处理，在C++中的异常处理更为复杂。

编译器会将 throw 语句翻译成一对 libstdc++ 库里的函数，包括为异常处理分配内存、调用 libstdc 来进行栈展开(stack unwinding)。
对于每个 catch 语句的存在，编译器会在函数末尾加上一些特殊信息，包括当前函数可以捕获的异常表，以及清理表(cleanup table)。
在进行栈展开时，会调用 libstdc++ 提供的特殊函数(称为 personality routine)，会检查栈上的所有函数哪个异常可以被捕获。
如果异常无法被捕获，那么 std::terminate 就会被调用。
如果找到了能够匹配的捕获操作，展开处理(unwinder)会再次在栈顶进行操作。
unwinder 第二次遍历栈时，会要求 personality routine 去为当前函数执行清理操作。
personality routine 会检查当前函数的清理表。如果有什么清理操作要执行的话，就会直接跳到当前栈帧(stack frame)，执行清理操作(cleanup code)。这会引起每个在当前作用域分配的对象的析构操作。
一旦 unwinder 到达了可以处理异常的栈帧时，它会跳到对应的 catch 语句当中。
执行完 catch 语句后，会调用清理函数去释放掉为异常所分配的内存。