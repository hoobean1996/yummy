program break:
随着内存分配和释放，堆的大小是可以变化的，当前的堆的边界称为 program break

brk, sbrk:
系统调用 brk, sbrk能够可以操控program break.
brk设置program break为指定的位置
```c++
int brk(void *end_data_segment);


void *sbrk(intptr_t increment);
```
c程序更多的使用malloc 和 free进行分配和释放内存

```c++

void *malloc(size_t size);
void free(void *ptr);
```
malloc 用于在堆上分配size大小的内存，并返回指向新分配内存起始位置的指针。
free用于释放指向的内存块，一般情况下，free并不会降低program break的位置，而是添加到可用列表中

mtrace和muntrace函数分别在程序中打开和关闭堆内存分配调用进行追踪堆功能。
mcheck和mprobe函数允许程序对已经分配到内存进行一执行检查。

mallopt能够修改glibc中malloc相关的参数

```c++
void *calloc(size_t numitems, size_t size);
void *realloc(void *ptr, size_t size);
```
calloc函数用于给一组相同的对象分配内存
realloc用于调整一块内存的大小

分配对齐的内存
```c++
void *memalign(size_t boundary, size_t size)
```
memalign分配size个字节的内存，起始地址是参数boundary的整数倍

