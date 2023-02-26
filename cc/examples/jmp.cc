#include <cstdio>
#include <setjmp.h>

static jmp_buf env;

static void f2(void) { longjmp(env, 2); }

static void f1(int argc) {
  if (argc == 1) {
    longjmp(env, 1);
  }
  f2();
}

int main(int argc, char *argv[]) {
  // 第一次调用setjmp 返回0，设置跳转回来的位置
  // 进入f1以后，longjmp会再次跳回来，这次setjmp的返回值就是longjmp中传递的参数值
  switch (setjmp(env)) {
  case 0:
    printf("calling f1() after inital setjmp()\n");
    f1(argc);
    break;
  case 1:
    printf("we jmped back from f1() \n");
    break;
  case 2:
    printf("we jumped back from f2() \n");
    break;
  }
  return 0;
}