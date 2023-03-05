device:
设备专用文件和系统中的某个设备相对应。

字符型设备基于字符处理数据。 terminal、keyboard
块设备基于块处理数据， disk

device id:
每个设备文件都是master id, support id


disk driver:
disk -> track -> sector -> phsical block (512 bytes)


磁盘分区：
可以将磁盘划分为一个或者多个不重叠的分区，每个分区都相当于一个独立的设备 /proc/partitions
磁盘分区可以容纳任何类型的信息，一般有
- 文件系统: mkfs可以创建文件系统
- 数据区域
- 交换区域: mkswap可以创建


fs:
ext2
FAT, FAT32, NTFS
ext3, ext4, ... 可以在 /proc/filesystems查看所有的文件系统

fuse:
Linux支持FUSE，可以给内核hook，使得能够在用户空间程序实现文件系统

disk = block, block, ..., block

fs: [driver block, super block, inode table, data block]
所有的文件系统都有driver block, 用于引导操作系统，虽然没用，但是有。
超级块，包含与文件系统相关的参数信息
  inode table 大小
  fs 逻辑块的大小
  文件系统的大小
inode table: 文件系统中的每个文件或者目录都对应一个inode

inode:
  file type
  uid
  gid
  permission
  timestamps
  size

  ...


vfs:
Linux支持各种各样的文件系统，虚拟文件系统是内核特性，通过文件系统操作创建抽象层来解决问题

标准接口
open, read, write, lseek, close, truncate, stat, mount, umount, mmap, mkdir, link,
unlink, symlink, rename


log fs:
ext2的短板在于系统崩溃以后，为了保证系统的完整性，需要进行一致性检查，对于大型文件系统的话，可能会非常久。

采用日志文件系统，那么久不需要一致性检查。
tradeoff是增加了文件更新的时间。

Reiserfs: 可以将小文件与文件元数据装入相同的磁盘快，就会节省空间。
ext3: 给ext2加上日志功能
ext4
btrfs: butter fs 现代化文件系统

mount:
mount device directory 会把device的文件系统挂在到directory的目录，既文件系统的挂载点。


/proc/mounts 可以查看当前已经挂在的文件系统
/etc/fstab 包含了对系统支持的所有文件系统的描述

```c++
int mount(const char *source ,const char *target, const char *fstype, unsigned long mountflags, const void *data);

int umount(const char *target);
```


tmpfs:
tmpfs是在内存中的文件系统，由于不涉及磁盘访问，所以极快。

用途：可以用来进行共享内存， 用来实现posix信号量


查看文件系统的信息:
```c++
int statvfs(const char *pathname, struct statvfs *statvfsbuf);
int fstatvfs(int fd, struct statvfs *statvfsbuf);
```
许多文件系统都支持为超级用户预留文件系统块，用于在disk空间不足的时候 ，他们也能登录解决问题。