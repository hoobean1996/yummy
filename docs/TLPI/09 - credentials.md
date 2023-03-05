每个进程都有一套用数字表示的id

- real user ID, real group ID
- effective user ID, effective group ID
- saved set-user-ID, saved set-group ID
- file-system user ID, file-system group ID

当运行set-user ID程序的时候，内核会把进程的 effective user ID设置为可执行文件的用户ID

```c++
uid_t getuid(void);
uid_t geteuid(void);
gid_t getgid(void);
gid_t getegid(void);

int setuid(uid_t uid);
int setgid(uid_t gid);

```