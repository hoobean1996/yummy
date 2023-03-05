```c++

// 返回当前的时间
int gettimeofday(struct timeval*, struct timezeon*);

// 返回Epoch的秒数
time_t time(time_t *timep);
```

time_t:
// 将time_t转化为字符串
```c++
char *ctime(const char* timep);
```

time_t -> struct tm:

```c++
struct tm *gmtime(const time_t  *timep);
struct tm *localtime(const time_t *timep);
```

struct tm -> time_t:
```c++
time_t mktime(struct tm *timeptr);
```

```c++
char *asctime(const struct tm *timeptr);

size_t strftime(char *outstr, size_t maxsize, const char *format, const struct tm *timeptr);
```

timezone:

/usr/share/zoneinfo 在该目录下每个文件都包含了一个特定国家或者地区的相关信息


locale:
地区时是用于完成本地化的任务

language [_territory][.codeset][@modifier]

language ISO字母语言代码
territory ISO双字母国家代码
codeset 字符编码集

```c++
char *setlocale(int category, const char *locale);
```

更新系统时钟:

```c++
int settimeofday(const struct timeval *tv, const struct timezone *tz);

int adjtime(struct timeval *delta, struct timeval *olddelta);

```

软件时钟(jiffies)
时间相关的各种系统调用都受限于系统软件时钟的精度，度量单位是jiffies.
比如软件时钟的速度是100hz，那么1jiffies = 10ms


process time:
用户CPU时间是用户模式下执行花费的时间， virtual time
系统CPU时间是用户在内核模式执行花费的时间

可以利用times系统调用来检索进程的时间信息。
```c++
clock_t times(struct tms *buf);

// 返回进程使用的总的CPU时间
clock_t clock(void);
```