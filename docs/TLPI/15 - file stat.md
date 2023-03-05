```c++
int stat(const char *pathname, struct stat *statbuf);
int lstat(const char *pathname, struct stat *statbuf);
int fstat(int fd, struct stat *statbuf);
```
利用系统调用stat相关的，可以获取文件相关的信息。

利用utime， utimes来改变文件时间戳

```c++
int utime(const char *pathname, const struct timebuf *buf);
```


```c++
int access(const char *pathname, int mode); // 利用真实的uid， gid来检查文件访问权限


mode_t umask(mode_t mask);
```