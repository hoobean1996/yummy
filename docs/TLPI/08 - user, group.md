/etc/passwd
/etc/shadown: 加密的密码存放在这里，需要有特权的程序才能读取。
/etc/group: 组文件

```c++
struct passwd *getpwnam(const char *name);
struct passwd *getpwuid(uid_t uid);

struct group *getgrname(const char *name);
struct group *getgrgid(gid_t gid);
```
利用库函数从密码文件中获取记录。

扫描密码文件和组文件的所有记录
```c++
struct passwd getpwent(void);

void setpwent(void);
void endpwent(void);
```

密码加密
```c++
char *crypt(const char *key, const char *salt);
```