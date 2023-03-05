/proc:
/proc是一个虚拟文件系统，用来展示process相关的东西。

在/proc/PID下有很多属性:
cmdline
cwd
environ
exe
fd
maps
mem
mounts
root
status
task

此外/proc目录下还有很多系统信息
/proc 各种系统信息 
/proc/net 有关网络和套接字的状态信息 
/proc/sys/fs 文件系统相关设置 
/proc/sys/kernel 各种常规的内核设置 
/proc/sys/net 网络和套接字的设置 
/proc/sys/vm 内存管理设置 
/proc/sysvipc 有关System V IPC 对象的信息


uname:
```c++
int  uname(struct utsname *utsbuf);
```
uname 系统调用返回一系列关于主机系统的标识信息