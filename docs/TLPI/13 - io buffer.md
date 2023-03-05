缓冲区高速缓存:
read 和 write不会直接发起磁盘访问，而且在kernel buffer cache之间复制数据.

总之，如果需要发生大量的数据传输，采用大块空间缓冲数据，能够执行更少的系统调用，极大的提高IO性能。

设置stdio库的缓冲

fprintf
fscanf
fgets
fputs
fputc
fgetc

```c++
// 需要修改哪个文件流的缓冲
int setvbuf(FILE *stream, char *buf, int mode, size_t size);

void setbuf(FILE *stream, char *buf);

void setbuffer(FILE *stream, char *buf, size_t size)

int fflush(FILE *stream);
```

_IONBF => 不进行缓冲
_IOLBF => 行缓冲
_IOFBF => 全缓冲

fflush强制刷新缓冲区

fsync:
fsync系统调用会将缓冲数据和打开文件描诉符fd相关的数据刷新到磁盘
```c++
int fsync(int fd);

int fdatasync(int fd);

void sync(void);
```


user data 

stdio functions

stdio buffer

i/o syscall 

kernel buffer

kernel to disk

控制内核io模式

```c++
int posix_fadivse(int fd, off_t offset, off_t len, int advice);
```
POSIX_FADV_NORMAL 
进程对访问模式并无特别建议。如果没有建议，这就是默认行为。在Linux 中，该操作将
文件预读窗口大小置为默认值（128KB）。  
POSIX_FADV_SEQUENTIAL 
进程预计会从低偏移量到高偏移量顺序读取数据。在Linux 中，该操作将文件预读窗口大
小置为默认值的两倍。  
POSIX_FADV_RANDOM 
进程预计以随机顺序访问数据。在Linux 中，该选项会禁用文件预读。  
POSIX_FADV_WILLNEED 
进程预计会在不久的将来访问指定的文件区域。内核将由offset 和len 指定区域的文件数
据预先填充到缓冲区高速缓存中。后续对该文件的 read()调用将不会阻塞磁盘 I/O，只需从缓
冲区高速缓存中抓取数据即可。对于从文件读取的数据在缓冲区高速缓存中能保留多长时间，
内核并无保证。如果其他进程或内核的活动对内存存在强劲需求，那么最终会重用到这些页
面。换言之，如果内存压力高，程序员就应该确保 posix_fadvise()调用和后续 read()调用间的
总运行时长较短。（Linux 特有的系统调用readahead()提供了与POSIX_FADV_WILLNEED 操
作等效的功能。）  
POSIX_FADV_DONTNEED 
进程预计在不久的将来将不会访问指定的文件区域。这一操作给内核的建议是释放相关的
高速缓存页面（如果存在的话）。在Linux 中，该操作将分两步执行。首先，如果底层设备目前
没有挤满一系列排队的写操作请求，那么内核会对指定区域中已修改的页面进行刷新。之后，


direct i/o:
直接绕过缓冲区高速缓存，直接写到磁盘
会有很多限制
1. 传递数据的缓冲区，内存边界必须是块大小的整数倍
2. 数据传输的开始点，必须是快大小的整数倍
3. 数据块的长度必须是块大小的整数倍

需要用到memalign函数

```c++

int fileno(FILE *stream); // 返回fd

FILE *fdopen(int fd, const char *mode); // 通过fd打开FILE

```