# GCC compile options

-E 只产生预处理输出
-S 只产生汇编代码
-C 只产生编译代码 没有link
-l 链接共享库
-fPIC 当产生共享库的时候,产生位置无关的代码
-D 使用编译的时候的宏
-Werror 将警告升级为错误
-I 指定头文件的文件夹
-std 指定C++标准
-static 生成静态链接文件

```c++
#ifdef MY_MACRO
  printf("...");
#endif

gcc -Wall -DMY_MACRO main.c -o main
```