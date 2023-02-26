user:

/etc/passwd
- group id: 整数id
- home directory: 用户登录以后的初始目录
- login shell: 执行用户命令的程序的名字


/etc/group
- group name
- group id
- user list, split by comma

super user
user id = 0, 登录名通常为root

symbol link:
符号链接是经过特殊标记的文件，内容包含了另外一个文件的名字。
一般来说，当用到了路径名的时候，内核会自动解除符号链接的引用，用它指向的文件来替换符号链接，若目标文件也是一个符号链接，则会递归的处理下去。
如果符号链接指向的文件不存在，那么就是dangling link


pwd
每个进程都有一个当前工作目录

io:
open, read, write, close统一的io模型，本质上内核只提供一种文件类型，就是字节流序列，在处理磁盘文件的时候，我们可以利用lseek来进行随机访问

fd:
I/O 系统调用使用fd（非负整数）来指代打开的文件，获取fd的常用手法是open

通常，由shell启动的进程会继承三个已经打开的fd
0 - stdin
1 - stdout
2 - stderr

在C语言中，执行文件I/O的时候，通常会调用stdio的函数库.
fopen,fclose, scanf, printf, fgets, fputs 等

filter:
从std读取输入，加以转化，在将转化以后的数据输出到stdout，这种类型的程序
称为filter
cat, grep, tr, sort, wc, sed, awk等


cli arguments:
```c
int main(int argc, char *argv[]) {}
```

process:
进程是正在执行的程序实例，执行程序的时候，内核会将程序代码载入到虚拟内存，
为程序分配空间，建立内核bookkeeping数据结构，来记录与程序有关的信号

process layout:
text, data, heap, stack

进程可以利用fork来创建一个新进程，调用fork的称为parent process, 新创建的称为child process
内核通过复制父进程来创建子进程，子进程可以修改上述内容来执行新的代码。一般来说，子进程可以调用
execve来加载冰执行一个全新的程序

每个进程都有一个唯一的整数id，称为pid

有两种方式可以终止一个进程：
exit() 库函数 _exit系统调用，或者是向进程传递信号，将其杀死，无论以任何方式退出，进程都会生成终止状态，一个非负整数，可供父进程的wait系统调用检测。

每个进程都有一组与之相关的 uid和gid
- real uid, gid: 用来标识进程所属的用户和组。 新进程会从父进程继承
- effective uid, gid: 进程在访问受保护资源的时候，会利用这两个id来确定访问权限。一般情况下，和real uid, gid相同
- 补充组 id：用来标识进程所属的额外组。新进程会从其父进程继承

super priviledge process:
在unix系统上，特权进程实质有效用户id为0的进程。
由某个特权进程创建的进程，也是特权进程。 比如由root用户发起的login shell
另外一种是利用set-user-id机制，该机制允许某进程的有效用户等于该进程所执行文件的用户id

capabilities:
Linux把传统上赋予给超级用户的权限划分为一组相互独立的单元。特权进程相当于开启了所有能力

init:
系统引导的时候，内核会创建一个名为init的特殊进程，是所有进程的parent。系统中所有的进程，都是其后代。
init的pid = 1

daemon:
daemon process是指具有特殊用户的进程，系统创建和管理此类进程的方法没有什么不一样，
- daemon会存活直到系统关闭
- 守护进程在后台运行，无控制终端供其读取或者写入数据
syslogd, httpd

env list:
每个进程都有一份环境列表，即在进程用户空间内存中维护的一组环境变量。由fork创建的进程，会进程父进程的环境列表。
在大多数shell中，export命令可以用来创建环境变量
c语言程序可以利用 char **environ来访问环境

quota:
每个进程都会消耗资源，使用系统调用setrlimit可以为各类资源设定一个上限。也可以使用ulimit调整shell的资源限制，shell创建的子进程会继承该配置。

mmap:
调用系统函数mmap的进程，会在其虚拟地址空间中创建一个新的内存映射：
- 文件映射：将文件的部分区域映射到内存，映射完成后，对文件映射内容的访问就转化为了相关的内存区域的字节操作。
- 匿名映射就是无文件关联，同时初始化为0


static lib,s shared lib

ipc:
1. signal: 用来表示事件的发生
2. pipe: 用来在进程之间传递数据
3. socket: 用来不同主机的进程之间传递数据
4. flock: 为了防止其他进程读取和更新文件内容，允许某进程对文件进行锁定
5. message queue: 用于在进程间交换信息
6. semaphore: 用来同步进程的动作
7. shared memory: 用来允许多个进程同时访问一个内存


progress group:
login shell执行的时候都会在一个新进程内发起，
ls -l | sort -k5n | less
其实创建了3个进程

会将管道内的所有进程置于一个新的进程组或者人物中，进程中的每个进程都具有相同的进程组标识符，这个标识符其实就是其中某个进程的pid。这个进程也称为process group leader


session, control terminal, control process:
会话实质一组进程组。会话中所有的进程都具有相同的会话标识符。 session leader是指创建会话的进程。

使用session最多的是支持任务控制的shell。

通常，session都和某个控制终端相关，control terminal创建于session的第一个进程初次打开terminal的时候。
对于交互式shell所创建的会话，control terminal就是用户的登录终端

pty:
ptr是一对相互连接的虚拟设备，称为主从设备。
从slave device所提供的接口，其行为方式和终端类似。基于该特点，可以将某个终端编写的程序和slave device连接起来，然后在利用连接到master到另外一个程序来驱动这个面向终端的程序。
telnet, ssh


/proc fs:
/proc文件系统是一种虚拟文件系统，以文件系统目录和文件形式，提供一个内核数据结构的接口。