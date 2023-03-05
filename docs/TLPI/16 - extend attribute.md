扩展属性能够以name-value的形式将任意元数据和文件inode进行关联。
利用它来实现acl和文件capability。

```c++

int setxattr()

int lsetxattr()


int fsetxattr()
```