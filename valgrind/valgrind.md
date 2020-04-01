valgrind
========

## valgrind介绍

Valgrind是一套Linux下，开放源代码（GPL V2）的仿真调试工具的集合。
Valgrind由内核（core）以及基于内核的其他调试工具组成。内核类似于一个框架（framework），
它模拟了一个CPU环境，并提供服务给其他工具；而其他工具则类似于插件 (plug-in)，
利用内核提供的服务完成各种特定的内存调试任务。

Valgrind的体系结构如下图所示:
![valgrind-core](./valgrind-core.jpg)

valgrind包含的工具有:
* Memcheck。这是valgrind应用最广泛的工具，一个重量级的内存检查器，
  能够发现开发中绝大多数内存错误使用情况，比如：使用未初始化的内存，
  使用已经释放了的内存，内存访问越界等。这也是本文将重点介绍的部分。

* Callgrind。它主要用来检查程序中函数调用过程中出现的问题。

* Cachegrind。它主要用来检查程序中缓存使用出现的问题。

* Helgrind。它主要用来检查多线程程序中出现的竞争问题。

* Massif。它主要用来检查程序中堆栈使用中出现的问题。

* Extension。可以利用core提供的功能，自己编写特定的内存调试工具

## linux下内存空间分布图

![linux-ram](./linux-ram.jpg)

一个典型的linux C程序内存空间由如下几部分组成:

* 代码段（.text）
  这里存放的是CPU要执行的指令。代码段是可共享的，
  相同的代码在内存中只会有一个拷贝，同时这个段是只读的，防止程序由于错误而修改自身的指令。

* 初始化数据段（.data）
  这里存放的是程序中需要明确赋初始值的变量，
  例如位于所有函数之外的全局变量：int val="100"。需要强调的是，
  以上两段都是位于程序的可执行文件中，内核在调用exec函数启动该程序时从源程序文件中读入。

* 未初始化数据段（.bss）
  位于这一段中的数据，内核在执行该程序前，将其初始化为0或者null。
  例如出现在任何函数之外的全局变量：int sum;

* 堆（Heap）
  这个段用于在程序中进行动态内存申请，例如经常用到的malloc，new系列函数就是从这个段中申请内存。

* 栈（Stack）
  函数中的局部变量以及在函数调用过程中产生的临时变量都保存在此段中。

## 检测原理

* 当要读写内存中某个字节时，首先检查这个字节对应的 A bit。
  如果该A bit显示该位置是无效位置，memcheck 则报告读写错误。

* 内核（core）类似于一个虚拟的 CPU 环境，这样当内存中的某个字节被加载到真实的 CPU 中时，
  该字节对应的 V bit 也被加载到虚拟的 CPU 环境中。一旦寄存器中的值，被用来产生内存地址，
  或者该值能够影响程序输出，则 memcheck 会检查对应的V bits，如果该值尚未初始化，
  则会报告使用未初始化内存错误。

### Memcheck - 能够检测出内存问题，关键在于其建立了两个全局表。
* Valid-Value 表
  对于进程的整个地址空间中的每一个字节(byte)，都有与之对应的 8 个 bits；
  对于 CPU 的每个寄存器，也有一个与之对应的 bit 向量。
  这些 bits 负责记录该字节或者寄存器值是否具有有效的、已初始化的值。

* Valid-Address 表
  对于进程整个地址空间中的每一个字节(byte)，还有与之对应的 1 个 bit，
  负责记录该地址是否能够被读写。

### helgrind - 能够检测出多线程问题

### callgrind - 性能分析
执行这个命令后，会生成一个文件"callgrind.out.进程号"。注意，对于daemon进程的调试，不要通过kill -9方式停止。


## valgrind使用

### 用法

```sh
    valgrind [options] prog-and-args [options]
```

#### 常用选项，适用于所有valgrind工具

* -tool=<name>                      最常用的选项。运行 valgrind中名为toolname的工具。默认memcheck。
* h –help                           显示帮助信息。
* -version                          显示valgrind内核的版本，每个工具都有各自的版本。
* q –quiet                          安静地运行，只打印错误信息。
* v –verbose                        更详细的信息, 增加错误数统计。
* -trace-children=no|yes            跟踪子线程? [no]
* -track-fds=no|yes                 跟踪打开的文件描述？[no]
* -time-stamp=no|yes                增加时间戳到LOG信息? [no]
* -log-fd=<number>                  输出LOG到描述符文件 [2=stderr]
* -log-file=<file>                  将输出的信息写入到filename.PID的文件里，PID是运行程序的进行ID
* -log-file-exactly=<file>          输出LOG信息到 file
* -log-file-qualifier=<VAR>         取得环境变量的值来做为输出信息的文件名。 [none]
* -log-socket=ipaddr:port           输出LOG到socket ，ipaddr:port

#### log信息输出

* -xml=yes                          将信息以xml格式输出，只有memcheck可用
* -num-callers=<number>             show <number> callers in stack traces [12]
* -error-limit=no|yes               如果太多错误，则停止显示新错误? [yes]
* -error-exitcode=<number>          如果发现错误则返回错误代码 [0=disable]
* -db-attach=no|yes                 当出现错误，valgrind会自动启动调试器gdb。[no]
* -db-command=<command>             启动调试器的命令行选项[gdb -nw %f %p]

#### Memcheck - 相关选项

* -leak-check=no|summary|full       要求对leak给出详细信息? [summary]
* -leak-resolution=low|med|high     how much bt merging in leak check [low]
* -show-reachable=no|yes            show reachable blocks in leak check? [no]

#### helgrind - 相关选项


#### callgrind - 相关选项

* -separate-threads=yes             调试线程性能，这样会为每个线程单独生成一个性能分析文件


#### 见的内存问题

* 使用未初始化的内存
    局部变量和动态申请的变量，其初始值为随机值。
    如果程序使用了随机值的变量，那么程序的行为变得不可预测。

* 内存读写越界
    访问了你不应该/没有权限访问的内存地址空间，
    比如访问数组时越界；对动态内存访问时超出了申请的内存大小范围。

* 内存覆盖
    C 语言的强大和可怕之处在于其可以直接操作内存，
    C 标准库中提供了大量这样的函数，比如 strcpy, strncpy, memcpy, strcat等。
	  这些函数有一个共同的特点就是需要设置源地址 (src)，和目标地址(dst)，
	  src 和 dst 指向的地址不能发生重叠，否则结果将不可预期。

* 动态内存管理错误
    动态分配函数包括：malloc, new等，动态释放函数包括free, delete。
    成功申请了动态内存，就需要对其进行内存管理，而这又是最容易犯错误的。
    常见的包括：
        <申请和释放不一致> ：malloc/free，new/delete匹配调用，如调用一个释放两次
	    <释放后仍然读写  > ：释放后再使用就会覆盖别的数据，最好设置为NULL

* 内存泄露
    内存泄露(Memory leak): 动态申请的内存在使用完后既没有释放，又无法被程序的其他部分访问。
    内存泄露是在开发大型程序中最令人头疼的问题，
    防止内存泄露要从良好的变成习惯做起，并加强单元测试，同时可以使用memcheck检测

> 注意：
>    Valgrind不能检测静态数组的边界(在栈上分配的空间)。
>    Valgrind缺点是会消耗更多的内存(最大两倍于你源程序的内存)


## callgrind - 程序性能分析

### 生成性能分析数据

```sh
valgrind --tool=callgrind --separate-threads=yes ./test
```
如果不是多线程就不需要加参数`--separate-threads=yes`，执行完毕后，
会生成`callgrind.out.68686`文件，以及子线程文件`callgrind.out.68686-01`等。

### 把性能数据转换成doa格式数据
可以使用gprof2dot.py脚本，把callgrind生成的性能分析数据转换成dot格式的数据。方便使用dot把分析数据图形化。

```sh
python gprof2dot.py -f callgrind -n10 -s callgrind.out.68686 > valgrind.dot
```

### 使用dot把数据生成图片

```sh
dot -Tpng valgrind.dot -o valgrind.png
```

## helgrind - 线程同步问题

### 资源不安全访问 (就是多个线程在没有同步的情况下写某个资源体)

```c
#include <pthread.h>

int var = 0;

void* child_fn(void* arg)
{
    var++;
    return NULL;
}

int main(void)
{
    pthread_t child;
    pthread_t child2;

    pthread_create(&child,NULL, child_fn, NULL);
    pthread_create(&child2,NULL,child_fn,NULL);

    pthread_join(child,NULL);
    pthread_join(child2,NULL);

    return 0;
}
```

编译并测试：

    $ gcc thread.c -g -o thread
    $ ./valgrind --tool=helgrind ./thread

> note: 编译时必须加上`-g`选项

运行结果如下:

    uso@u-os:$ ./valgrind --tool=helgrind ../../../thread_helgrind
    ==10552== Helgrind, a thread error detector
    ==10552== Copyright (C) 2007-2017, and GNU GPL'd, by OpenWorks LLP et al.
    ==10552== Using Valgrind-3.13.0 and LibVEX; rerun with -h for copyright info
    ==10552== Command: ../../../thread_helgrind
    ==10552==
    ==10552== ---Thread-Announcement------------------------------------------
    ==10552==
    ==10552== Thread #3 was created
    ==10552==    at 0x516339E: clone (clone.S:74)
    ==10552==    by 0x4E45149: create_thread (createthread.c:102)
    ==10552==    by 0x4E46E83: pthread_create@@GLIBC_2.2.5 (pthread_create.c:679)
    ==10552==    by 0x4C34653: pthread_create_WRK (hg_intercepts.c:427)
    ==10552==    by 0x4C35737: pthread_create@* (hg_intercepts.c:460)
    ==10552==    by 0x400720: main (thread_helgrind.c:18)
    ==10552==
    ==10552== ---Thread-Announcement------------------------------------------
    ==10552==
    ==10552== Thread #2 was created
    ==10552==    at 0x516339E: clone (clone.S:74)
    ==10552==    by 0x4E45149: create_thread (createthread.c:102)
    ==10552==    by 0x4E46E83: pthread_create@@GLIBC_2.2.5 (pthread_create.c:679)
    ==10552==    by 0x4C34653: pthread_create_WRK (hg_intercepts.c:427)
    ==10552==    by 0x4C35737: pthread_create@* (hg_intercepts.c:460)
    ==10552==    by 0x400705: main (thread_helgrind.c:17)
    ==10552==
    ==10552== ----------------------------------------------------------------
    ==10552==
    ==10552== Possible data race during read of size 4 at 0x60104C by thread #3
    ==10552== Locks held: none
    ==10552==    at 0x4006BE: child_fn (thread_helgrind.c:8)
    ==10552==    by 0x4C34847: mythread_wrapper (hg_intercepts.c:389)
    ==10552==    by 0x4E466B9: start_thread (pthread_create.c:333)
    ==10552==
    ==10552== This conflicts with a previous write of size 4 by thread #2
    ==10552== Locks held: none
    ==10552==    at 0x4006C7: child_fn (thread_helgrind.c:8)
    ==10552==    by 0x4C34847: mythread_wrapper (hg_intercepts.c:389)
    ==10552==    by 0x4E466B9: start_thread (pthread_create.c:333)
    ==10552==  Address 0x60104c is 0 bytes inside data symbol "var"
    ==10552==
    ==10552== ----------------------------------------------------------------
    ==10552==
    ==10552== Possible data race during write of size 4 at 0x60104C by thread #3
    ==10552== Locks held: none
    ==10552==    at 0x4006C7: child_fn (thread_helgrind.c:8)
    ==10552==    by 0x4C34847: mythread_wrapper (hg_intercepts.c:389)
    ==10552==    by 0x4E466B9: start_thread (pthread_create.c:333)
    ==10552==
    ==10552== This conflicts with a previous write of size 4 by thread #2
    ==10552== Locks held: none
    ==10552==    at 0x4006C7: child_fn (thread_helgrind.c:8)
    ==10552==    by 0x4C34847: mythread_wrapper (hg_intercepts.c:389)
    ==10552==    by 0x4E466B9: start_thread (pthread_create.c:333)
    ==10552==  Address 0x60104c is 0 bytes inside data symbol "var"
    ==10552==
    ==10552==
    ==10552== For counts of detected and suppressed errors, rerun with: -v
    ==10552== Use --history-level=approx or =none to gain increased speed, at
    ==10552== the cost of reduced accuracy of conflicting-access information
    ==10552== ERROR SUMMARY: 2 errors from 2 contexts (suppressed: 0 from 0)

> note: 从上面的`data race`可以看出，出现了数据竞争，并且发生在`child_fn`函数的第8行。

### 死锁问题
对于helgrind可以检测出加锁解锁顺序出现问题导致的死锁问题

```c
#include <stdio.h>
#include <pthread.h>

pthread_mutex_t mute;
int var = 0;

void* child_fn(void* arg)
{
    pthread_mutex_lock(&mute);
    var++;
    pthread_mutex_lock(&mute);
    return NULL;
}

int main(void)
{
    pthread_t child;
    pthread_t child2;

    pthread_mutex_init(&mute, NULL);

    pthread_create(&child,NULL, child_fn, NULL);
    pthread_create(&child2,NULL,child_fn,NULL);

    pthread_join(child,NULL);
    pthread_join(child2,NULL);

    return 0;
}
```

运行结果如下:

    uso@u-os:$ ./valgrind --tool=helgrind ../../../thread_helgrind 
    ==11380== Helgrind, a thread error detector
    ==11380== Copyright (C) 2007-2017, and GNU GPL'd, by OpenWorks LLP et al.
    ==11380== Using Valgrind-3.13.0 and LibVEX; rerun with -h for copyright info
    ==11380== Command: ../../../thread_helgrind
    ==11380== 
    ^C==11380== 
    ==11380== Process terminating with default action of signal 2 (SIGINT)
    ==11380==    at 0x4E4798D: pthread_join (pthread_join.c:90)
    ==11380==    by 0x4C318F8: pthread_join_WRK (hg_intercepts.c:553)
    ==11380==    by 0x4C35742: pthread_join (hg_intercepts.c:572)
    ==11380==    by 0x400799: main (thread_helgrind.c:23)
    ==11380== ---Thread-Announcement------------------------------------------
    ==11380== 
    ==11380== Thread #2 was created
    ==11380==    at 0x516339E: clone (clone.S:74)
    ==11380==    by 0x4E45149: create_thread (createthread.c:102)
    ==11380==    by 0x4E46E83: pthread_create@@GLIBC_2.2.5 (pthread_create.c:679)
    ==11380==    by 0x4C34653: pthread_create_WRK (hg_intercepts.c:427)
    ==11380==    by 0x4C35737: pthread_create@* (hg_intercepts.c:460)
    ==11380==    by 0x40076D: main (thread_helgrind.c:20)
    ==11380== 
    ==11380== ----------------------------------------------------------------
    ==11380== 
    ==11380== Thread #2: Exiting thread still holds 1 lock
    ==11380==    at 0x4E4F26D: __lll_lock_wait (lowlevellock.S:135)
    ==11380==    by 0x4E48DBC: pthread_mutex_lock (pthread_mutex_lock.c:80)
    ==11380==    by 0x4C31C62: mutex_lock_WRK (hg_intercepts.c:902)
    ==11380==    by 0x4C35B1B: pthread_mutex_lock (hg_intercepts.c:925)
    ==11380==    by 0x400734: child_fn (thread_helgrind.c:11)
    ==11380==    by 0x4C34847: mythread_wrapper (hg_intercepts.c:389)
    ==11380==    by 0x4E466B9: start_thread (pthread_create.c:333)
    ==11380== 
    ==11380== 
    ==11380== For counts of detected and suppressed errors, rerun with: -v
    ==11380== Use --history-level=approx or =none to gain increased speed, at
    ==11380== the cost of reduced accuracy of conflicting-access information
    ==11380== ERROR SUMMARY: 1 errors from 1 contexts (suppressed: 0 from 0)

> note: 从打印的堆栈信息(`Exiting thread still holds 1 lock`)可以看到，
在同一个线程里面执行了两次`pthread_mutex_lock`

```c
#include <stdio.h>
#include <pthread.h>

pthread_mutex_t mute;
pthread_mutex_t mute2;
int var = 0;

void* child_fn(void* arg)
{
    pthread_mutex_lock(&mute);
    pthread_mutex_lock(&mute2);
    var++;
    pthread_mutex_unlock(&mute);
    pthread_mutex_unlock(&mute2);
    return NULL;
}

void* child_fn2(void* arg)
{
    pthread_mutex_lock(&mute2);
    pthread_mutex_lock(&mute);
    var++;
    pthread_mutex_unlock(&mute2);
    pthread_mutex_unlock(&mute);
    return NULL;
}

int main(void)
{
    pthread_t child;
    pthread_t child2;

    pthread_mutex_init(&mute, NULL);
    pthread_mutex_init(&mute2, NULL);

    pthread_create(&child,NULL, child_fn, NULL);
    pthread_create(&child2,NULL,child_fn2,NULL);

    pthread_join(child,NULL);
    pthread_join(child2,NULL);

    return 0;
}
```

运行结果如下:

    uso@u-os:$ ./valgrind --tool=helgrind ../../../thread_helgrind 
    ==13096== Helgrind, a thread error detector
    ==13096== Copyright (C) 2007-2017, and GNU GPL'd, by OpenWorks LLP et al.
    ==13096== Using Valgrind-3.13.0 and LibVEX; rerun with -h for copyright info
    ==13096== Command: ../../../thread_helgrind
    ==13096== 
    ==13096== ---Thread-Announcement------------------------------------------
    ==13096== 
    ==13096== Thread #3 was created
    ==13096==    at 0x516339E: clone (clone.S:74)
    ==13096==    by 0x4E45149: create_thread (createthread.c:102)
    ==13096==    by 0x4E46E83: pthread_create@@GLIBC_2.2.5 (pthread_create.c:679)
    ==13096==    by 0x4C34653: pthread_create_WRK (hg_intercepts.c:427)
    ==13096==    by 0x4C35737: pthread_create@* (hg_intercepts.c:460)
    ==13096==    by 0x4008B4: main (thread_helgrind.c:37)
    ==13096== 
    ==13096== ----------------------------------------------------------------
    ==13096== 
    ==13096== Thread #3: lock order "0x6010C0 before 0x601080" violated
    ==13096== 
    ==13096== Observed (incorrect) order is: acquisition of lock at 0x601080
    ==13096==    at 0x4C31CC7: mutex_lock_WRK (hg_intercepts.c:909)
    ==13096==    by 0x4C35B1B: pthread_mutex_lock (hg_intercepts.c:925)
    ==13096==    by 0x400815: child_fn2 (thread_helgrind.c:20)
    ==13096==    by 0x4C34847: mythread_wrapper (hg_intercepts.c:389)
    ==13096==    by 0x4E466B9: start_thread (pthread_create.c:333)
    ==13096== 
    ==13096==  followed by a later acquisition of lock at 0x6010C0
    ==13096==    at 0x4C31CC7: mutex_lock_WRK (hg_intercepts.c:909)
    ==13096==    by 0x4C35B1B: pthread_mutex_lock (hg_intercepts.c:925)
    ==13096==    by 0x40081F: child_fn2 (thread_helgrind.c:21)
    ==13096==    by 0x4C34847: mythread_wrapper (hg_intercepts.c:389)
    ==13096==    by 0x4E466B9: start_thread (pthread_create.c:333)
    ==13096== 
    ==13096== Required order was established by acquisition of lock at 0x6010C0
    ==13096==    at 0x4C31CC7: mutex_lock_WRK (hg_intercepts.c:909)
    ==13096==    by 0x4C35B1B: pthread_mutex_lock (hg_intercepts.c:925)
    ==13096==    by 0x4007CB: child_fn (thread_helgrind.c:10)
    ==13096==    by 0x4C34847: mythread_wrapper (hg_intercepts.c:389)
    ==13096==    by 0x4E466B9: start_thread (pthread_create.c:333)
    ==13096== 
    ==13096==  followed by a later acquisition of lock at 0x601080
    ==13096==    at 0x4C31CC7: mutex_lock_WRK (hg_intercepts.c:909)
    ==13096==    by 0x4C35B1B: pthread_mutex_lock (hg_intercepts.c:925)
    ==13096==    by 0x4007D5: child_fn (thread_helgrind.c:11)
    ==13096==    by 0x4C34847: mythread_wrapper (hg_intercepts.c:389)
    ==13096==    by 0x4E466B9: start_thread (pthread_create.c:333)
    ==13096== 
    ==13096==  Lock at 0x6010C0 was first observed
    ==13096==    at 0x4C35A83: pthread_mutex_init (hg_intercepts.c:787)
    ==13096==    by 0x40086F: main (thread_helgrind.c:33)
    ==13096==  Address 0x6010c0 is 0 bytes inside data symbol "mute"
    ==13096== 
    ==13096==  Lock at 0x601080 was first observed
    ==13096==    at 0x4C35A83: pthread_mutex_init (hg_intercepts.c:787)
    ==13096==    by 0x40087E: main (thread_helgrind.c:34)
    ==13096==  Address 0x601080 is 0 bytes inside data symbol "mute2"
    ==13096== 
    ==13096== 
    ==13096== 
    ==13096== For counts of detected and suppressed errors, rerun with: -v
    ==13096== Use --history-level=approx or =none to gain increased speed, at
    ==13096== the cost of reduced accuracy of conflicting-access information
    ==13096== ERROR SUMMARY: 1 errors from 1 contexts (suppressed: 9 from 9)

> note: 从上面的提示信息(`lock order "0x6010C0 before 0x601080" violated`)可以看出，
`child_fn`有两次加锁动作，分别在第10行和第11行，而`child_fn2`也有两个加锁动作，分别在第20行和第21行。


### POSIX pthreads API的错误使用

```c
```


运行结果如下:

### 将同步块尽量缩到最小 (这是一个很大的课题)

```c

```

运行结果如下:

## memcheck - 内存相关问题

### 使用未初始化内存
对于位于程序中不同段的变量，其初始值是不同的，全局变量和静态变量初始值为0，
而局部变量和动态申请的变量，其初始值为随机值。如果程序使用了为随机值的变量，那么程序的行为就变得不可预期。

```c
#include <stdio.h>

int main(int argc, const char *argv[])
{
    int a[5];
    int s;

    a[0] = a[1] = a[3] = a[4] = 0;

    for (int i = 0; i < 5; i++) {
        s += a[i];                          //a[2]未初始化
    }

    if (s == 666)
        printf("sum is %d \n", s);

    return 0;
}
```

编译并测试：

    $ gcc test.c -g -o test
    $ ./valgrind --tool=memcheck --leak-check=full ./test

> note: 编译时必须加上`-g`选项

运行结果如下:

    uso@u-os:$ ./valgrind --tool=memcheck --leak-check=full ./test
    ==7006== Memcheck, a memory error detector
    ==7006== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
    ==7006== Using Valgrind-3.13.0 and LibVEX; rerun with -h for copyright info
    ==7006== Command: ./test
    ==7006==
    ==7006== Conditional jump or move depends on uninitialised value(s)      ----> 提示使用了未初始化的内存
    ==7006==    at 0x4005F3: main (test.c:14)                                ----> 提示出错的代码行数
    ==7006==
    ==7006==
    ==7006== HEAP SUMMARY:
    ==7006==     in use at exit: 0 bytes in 0 blocks
    ==7006==   total heap usage: 0 allocs, 0 frees, 0 bytes allocated
    ==7006==
    ==7006== All heap blocks were freed -- no leaks are possible
    ==7006==
    ==7006== For counts of detected and suppressed errors, rerun with: -v
    ==7006== Use --track-origins=yes to see where uninitialised values come from
    ==7006== ERROR SUMMARY: 1 errors from 1 contexts (suppressed: 0 from 0)


### 内存读写越界
这种情况是指：访问了你不应该/没有权限访问的内存地址空间，
比如访问数组时越界；对动态内存访问时超出了申请的内存大小范围。

```c
#include <stdio.h>
#include <stdlib.h>

int main(int argc, const char *argv[])
{
    int len = 4;
    int *pt = (int *)malloc(len * sizeof(int));     //没有对应的free，造成了泄露
    int *p = pt;

    for (int i = 0; i < len; i++) {
        p++;
    }

    *p = 5;                                         //写，访问了非法的地址
    printf("the value of p equal: %d \n", *p);      //读，访问了非法的地址

    return 0;
}

```

运行结果如下：

    uso@u-os:$ ./valgrind --tool=memcheck --leak-check=full ./test
    ==7203== Memcheck, a memory error detector
    ==7203== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
    ==7203== Using Valgrind-3.13.0 and LibVEX; rerun with -h for copyright info
    ==7203== Command: ./test
    ==7203==
    ==7203== Invalid write of size 4
    ==7203==    at 0x4005B7: main (test.c:14)
    ==7203==  Address 0x5204050 is 0 bytes after a block of size 16 alloc'd
    ==7203==    at 0x4C2DBF6: malloc (vg_replace_malloc.c:299)
    ==7203==    by 0x40058C: main (test.c:7)
    ==7203==
    ==7203== Invalid read of size 4
    ==7203==    at 0x4005C1: main (test.c:15)
    ==7203==  Address 0x5204050 is 0 bytes after a block of size 16 alloc'd
    ==7203==    at 0x4C2DBF6: malloc (vg_replace_malloc.c:299)
    ==7203==    by 0x40058C: main (test.c:7)
    ==7203==
    the value of p equal: 5
    ==7203==
    ==7203== HEAP SUMMARY:
    ==7203==     in use at exit: 16 bytes in 1 blocks
    ==7203==   total heap usage: 2 allocs, 1 frees, 1,040 bytes allocated
    ==7203==
    ==7203== 16 bytes in 1 blocks are definitely lost in loss record 1 of 1
    ==7203==    at 0x4C2DBF6: malloc (vg_replace_malloc.c:299)
    ==7203==    by 0x40058C: main (test.c:7)
    ==7203==
    ==7203== LEAK SUMMARY:
    ==7203==    definitely lost: 16 bytes in 1 blocks
    ==7203==    indirectly lost: 0 bytes in 0 blocks
    ==7203==      possibly lost: 0 bytes in 0 blocks
    ==7203==    still reachable: 0 bytes in 0 blocks
    ==7203==         suppressed: 0 bytes in 0 blocks
    ==7203==
    ==7203== For counts of detected and suppressed errors, rerun with: -v
    ==7203== ERROR SUMMARY: 3 errors from 3 contexts (suppressed: 0 from 0)

### 在内存被释放后进行读/写

```c
#include <stdio.h>
#include <stdlib.h>

int main(int argc, const char *argv[])
{
    char *p = malloc(1);
    *p = 'a';
    printf("*p: %c \n", *p);
    free(p);

    char c = *p;
    printf("c: %c \n", c);

    return 0;
}
```

运行结果如下:

    uso@u-os:$ ./valgrind --tool=memcheck --leak-check=full ./test
    ==13621== Memcheck, a memory error detector
    ==13621== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
    ==13621== Using Valgrind-3.13.0 and LibVEX; rerun with -h for copyright info
    ==13621== Command: ./test
    ==13621== 
    *p: a 
    ==13621== Invalid read of size 1
    ==13621==    at 0x400605: main (test.c:11)
    ==13621==  Address 0x5204040 is 0 bytes inside a block of size 1 free'd
    ==13621==    at 0x4C2ECF0: free (vg_replace_malloc.c:530)
    ==13621==    by 0x400600: main (test.c:9)
    ==13621==  Block was alloc'd at
    ==13621==    at 0x4C2DBF6: malloc (vg_replace_malloc.c:299)
    ==13621==    by 0x4005CE: main (test.c:6)
    ==13621== 
    c: a 
    ==13621== 
    ==13621== HEAP SUMMARY:
    ==13621==     in use at exit: 0 bytes in 0 blocks
    ==13621==   total heap usage: 2 allocs, 2 frees, 1,025 bytes allocated
    ==13621== 
    ==13621== All heap blocks were freed -- no leaks are possible
    ==13621== 
    ==13621== For counts of detected and suppressed errors, rerun with: -v
    ==13621== ERROR SUMMARY: 1 errors from 1 contexts (suppressed: 0 from 0)

> note: 从提示信息(`Invalid read of size 1`)中可以看出，读取了非法内存。
虽然读出的数据是对的，但是该内存随时都可能发生改变，造成程序的跑飞

### 从已分配内存块的尾部进行读/写

```c
#include <stdio.h>
#include <stdlib.h>

int main(int argc, const char *argv[])
{
    char *p = malloc(1);
    *p = 'a';

    char c = *(p+1);
    printf("c: %c \n", c);

    free(p);

    return 0;
}
```

运行结果如下:

    uso@u-os:$ ./valgrind --tool=memcheck --leak-check=full ./test
    ==13699== Memcheck, a memory error detector
    ==13699== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
    ==13699== Using Valgrind-3.13.0 and LibVEX; rerun with -h for copyright info
    ==13699== Command: ./test
    ==13699== 
    ==13699== Invalid read of size 1
    ==13699==    at 0x4005DE: main (test.c:9)
    ==13699==  Address 0x5204041 is 0 bytes after a block of size 1 alloc'd
    ==13699==    at 0x4C2DBF6: malloc (vg_replace_malloc.c:299)
    ==13699==    by 0x4005CE: main (test.c:6)
    ==13699== 
    c:  
    ==13699== 
    ==13699== HEAP SUMMARY:
    ==13699==     in use at exit: 0 bytes in 0 blocks
    ==13699==   total heap usage: 2 allocs, 2 frees, 1,025 bytes allocated
    ==13699== 
    ==13699== All heap blocks were freed -- no leaks are possible
    ==13699== 
    ==13699== For counts of detected and suppressed errors, rerun with: -v
    ==13699== ERROR SUMMARY: 1 errors from 1 contexts (suppressed: 0 from 0)

### 两次释放内存

```c
#include <stdio.h>
#include <stdlib.h>

int main(int argc, const char *argv[])
{
    char *p = malloc(1);
    *p = 'a';

    free(p);
    free(p);

    return 0;
}
```

运行结果如下:

    uso@u-os:$ ./valgrind --tool=memcheck --leak-check=full ./test
    ==13806== Memcheck, a memory error detector
    ==13806== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
    ==13806== Using Valgrind-3.13.0 and LibVEX; rerun with -h for copyright info
    ==13806== Command: ./test
    ==13806== 
    ==13806== Invalid free() / delete / delete[] / realloc()
    ==13806==    at 0x4C2ECF0: free (vg_replace_malloc.c:530)
    ==13806==    by 0x4005A1: main (test.c:10)
    ==13806==  Address 0x5204040 is 0 bytes inside a block of size 1 free'd
    ==13806==    at 0x4C2ECF0: free (vg_replace_malloc.c:530)
    ==13806==    by 0x400595: main (test.c:9)
    ==13806==  Block was alloc'd at
    ==13806==    at 0x4C2DBF6: malloc (vg_replace_malloc.c:299)
    ==13806==    by 0x40057E: main (test.c:6)
    ==13806== 
    ==13806== 
    ==13806== HEAP SUMMARY:
    ==13806==     in use at exit: 0 bytes in 0 blocks
    ==13806==   total heap usage: 1 allocs, 2 frees, 1 bytes allocated
    ==13806== 
    ==13806== All heap blocks were freed -- no leaks are possible
    ==13806== 
    ==13806== For counts of detected and suppressed errors, rerun with: -v
    ==13806== ERROR SUMMARY: 1 errors from 1 contexts (suppressed: 0 from 0)

### 内存覆盖

C 语言的强大和可怕之处在于其可以直接操作内存，C 标准库中提供了大量这样的函数，
比如 strcpy, strncpy, memcpy, strcat 等，这些函数有一个共同的特点就是需要设置源地址 (src)，
和目标地址(dst)，src 和 dst 指向的地址不能发生重叠，否则结果将不可预期。

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, const char *argv[])
{
    char x[50];

    for (int i = 0; i < 50; i++) {
        x[i] = i + 1;
    }

    strncpy(x+20, x, 20);
    strncpy(x+20, x, 21);       //src和dst地址相差20，但是拷贝的长度是21

    strncpy(x, x+20, 20);
    strncpy(x, x+20, 21);       //src和dst地址相差20，但是拷贝的长度是21

    x[39] = '\0';
    strcpy(x, x+20);

    x[39] = 39;
    x[40] = '\0';
    strcpy(x, x+20);            //src和dst地址相差20，字符串遇'\0'结束，故此长度为21

    return 0;
}
```

运行结果如下：
```txt
==8193== Memcheck, a memory error detector
==8193== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
==8193== Using Valgrind-3.13.0 and LibVEX; rerun with -h for copyright info
==8193== Command: ./test
==8193==
==8193== Source and destination overlap in strncpy(0x1ffefffc89, 0x1ffefffc75, 21)
==8193==    at 0x4C310D6: __strncpy_sse2_unaligned (vg_replace_strmem.c:552)
==8193==    by 0x40064F: main (test.c:14)
==8193==
==8193== Source and destination overlap in strncpy(0x1ffefffc75, 0x1ffefffc89, 21)
==8193==    at 0x4C310D6: __strncpy_sse2_unaligned (vg_replace_strmem.c:552)
==8193==    by 0x400687: main (test.c:17)
==8193==
==8193== Source and destination overlap in strcpy(0x1ffefffc60, 0x1ffefffc74)
==8193==    at 0x4C30B96: strcpy (vg_replace_strmem.c:510)
==8193==    by 0x4006C1: main (test.c:24)
==8193==
==8193==
==8193== HEAP SUMMARY:
==8193==     in use at exit: 0 bytes in 0 blocks
==8193==   total heap usage: 0 allocs, 0 frees, 0 bytes allocated
==8193==
==8193== All heap blocks were freed -- no leaks are possible
==8193==
==8193== For counts of detected and suppressed errors, rerun with: -v
==8193== ERROR SUMMARY: 3 errors from 3 contexts (suppressed: 0 from 0)
```

### 动态内存管理

常见的内存分配方式分三种：静态存储，栈上分配，堆上分配。
全局变量属于静态存储，它们是在编译时就被分配了存储空间，函数内的局部变量属于栈上分配，
而最灵活的内存使用方式当属堆上分配，也叫做内存动态分配了。
常用的内存动态分配函数包括：malloc, alloc, realloc, new等，动态释放函数包括free, delete。

一旦成功申请了动态内存，我们就需要自己对其进行内存管理，而这又是最容易犯错误的。

### 常见的内存动态管理错误

* 申请和释放不一致
  C中使用的 malloc/alloc/realloc 方式申请的内存，用 free 释放;  
  C++兼容C，因为也包括C的内存申请方式，C++中使用new和delete。

>note: 必须严格配对使用

* 申请和释放不匹配
  申请了多少内存，在使用完成后就要释放多少。如果没有释放，或者少释放了就是内存泄露；多释放了也会产生问题。

* 释放后仍然读写
  本质上说，系统会在堆上维护一个动态内存链表，如果被释放，
  就意味着该块内存可以继续被分配给其他部分，如果内存被释放后再访问，就可能覆盖其他部分的信息，这是一种严重的错误

```c
#include <stdio.h>
#include <stdlib.h>

int main(int argc, const char *argv[])
{
    int i;
    char *p = (char *)malloc(10);
    char *pt = p;

    for (i = 0; i < 10; i++) {
        p[i] = 'z';
    }

    free(pt);
    pt[1] = 'x';    //释放堆内存后，再次使用

    return 0;
}
```

运行结果如下：
```txt
==8419== Memcheck, a memory error detector
==8419== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
==8419== Using Valgrind-3.13.0 and LibVEX; rerun with -h for copyright info
==8419== Command: ./test
==8419==
==8419== Invalid write of size 1
==8419==    at 0x4005C2: main (test.c:15)
==8419==  Address 0x5204041 is 1 bytes inside a block of size 10 free'd
==8419==    at 0x4C2ECF0: free (vg_replace_malloc.c:530)
==8419==    by 0x4005B9: main (test.c:14)
==8419==  Block was alloc'd at
==8419==    at 0x4C2DBF6: malloc (vg_replace_malloc.c:299)
==8419==    by 0x40057E: main (test.c:7)
==8419==
==8419==
==8419== HEAP SUMMARY:
==8419==     in use at exit: 0 bytes in 0 blocks
==8419==   total heap usage: 1 allocs, 1 frees, 10 bytes allocated
==8419==
==8419== All heap blocks were freed -- no leaks are possible
==8419==
==8419== For counts of detected and suppressed errors, rerun with: -v
==8419== ERROR SUMMARY: 1 errors from 1 contexts (suppressed: 0 from 0)
```

### 内存泄漏

内存泄露（Memory leak）指的是，在程序中动态申请的内存，在使用完后既没有释放，
又无法被程序的其他部分访问。内存泄露是在开发大型程序中最令人头疼的问题，
以至于有人说，内存泄露是无法避免的。其实不然，防止内存泄露要从良好的编程习惯做起，
另外重要的一点就是要加强单元测试（Unit Test），而memcheck就是这样一款优秀的工具。

在一个单独的函数中，每个人的内存泄露意识都是比较强的。但很多情况下，
我们都会对malloc/free 或new/delete做一些包装，以符合我们特定的需要，
无法做到在一个函数中既使用又释放。这个例子也说明了内存泄露最容易发生的地方：即两个部分的接口部分，
一个函数申请内存，一个函数释放内存。并且这些函数由不同的人开发、使用，
这样造成内存泄露的可能性就比较大了。这需要养成良好的单元测试习惯，将内存泄露消灭在初始阶段。

```c
#include <stdio.h>
#include <stdlib.h>

typedef struct _node {
    struct _node *l;
    struct _node *r;
    char v;

}node;

int count = 0;

node * mk(node *l, node *r, char val)
{
    node *f = (node *)malloc(sizeof(*f));
    count++;

    f->l = l;
    f->r = r;
    f->v = val;

    return f;
}

void nodefr(node *n)
{
    if (n) {
        nodefr(n->l);
        nodefr(n->r);
        free(n);
    }
}

int main(int argc, const char *argv[])
{
    node *tree1, *tree2, *tree3;

    tree1 = mk(mk(mk(NULL, NULL, '3'), NULL, '2'), NULL, '1');
    tree2 = mk(NULL, mk(NULL, mk(NULL, NULL, '6'), '5'), '4');
    tree3 = mk(mk(tree1, tree2, '8'), 0, '7');

    printf("count: %d, size(node): %ld \n", count, sizeof(struct _node));

    return 0;
}

```

运行结果如下：
```txt
==9630== Memcheck, a memory error detector
==9630== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
==9630== Using Valgrind-3.13.0 and LibVEX; rerun with -h for copyright info
==9630== Command: ./test
==9630==
count: 8, size(node): 24
==9630==
==9630== HEAP SUMMARY:
==9630==     in use at exit: 192 bytes in 8 blocks
==9630==   total heap usage: 9 allocs, 1 frees, 1,216 bytes allocated
==9630==
==9630== 192 (24 direct, 168 indirect) bytes in 1 blocks are definitely lost in loss record 8 of 8
==9630==    at 0x4C2DBF6: malloc (vg_replace_malloc.c:299)
==9630==    by 0x4005D4: mk (test.c:14)
==9630==    by 0x400701: main (test.c:39)
==9630==
==9630== LEAK SUMMARY:
==9630==    definitely lost: 24 bytes in 1 blocks
==9630==    indirectly lost: 168 bytes in 7 blocks
==9630==      possibly lost: 0 bytes in 0 blocks
==9630==    still reachable: 0 bytes in 0 blocks
==9630==         suppressed: 0 bytes in 0 blocks
==9630==
==9630== For counts of detected and suppressed errors, rerun with: -v
==9630== ERROR SUMMARY: 1 errors from 1 contexts (suppressed: 0 from 0)
```

该示例程序是生成一棵树的过程，每个树节点的大小为24（考虑内存对齐），共8个节点。从上述输出可以看出，所有的内存泄露都被发现。


Memcheck将内存泄露分为两种，一种是可能的内存泄露（Possibly lost），另外一种是确定的内存泄露（Definitely lost）。
Possibly lost 是指仍然存在某个指针能够访问某块内存，但该指针指向的已经不是该内存首地址。
Definitely lost 是指已经不能够访问这块内存。而Definitely lost又分为两种：直接的（direct）和间接的（indirect）。
直接和间接的区别就是，直接是没有任何指针指向该内存，间接是指指向该内存的指针都位于内存泄露处。在上述的例子中，根节点是directly lost，而其他节点是indirectly lost。


