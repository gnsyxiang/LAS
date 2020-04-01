coredump 
========

1、coredump产生的几种可能情况
内存越界；
多线程程序使用了线程不安全的函数；
多线程读写的数据未加锁保护，对于会被多个线程同时访问的全局数据，应该注意加锁保护；
非法指针，使用了空指针、随意使用指针转换；
堆栈益处，不要使用大的局部变量(因为局部变量都分配在堆栈上)。

2、不会产生CoreDump文件的情况
进程是设置-用户-ID，而且当前用户并非程序文件的所有者；
进程是设置-组-ID，而且当前用户并非该程序文件的组所有者；
用户没有写当前工作目录的许可权；
文件太大。core文件的许可权(假定该文件在此之前并不存在)通常是用户读/写，组读和其他读。

//----------------------------------------------------------------------------------
//-- 运用coredump

1、解除系统coredump限制
ulimit -a               //-- 查看系统

ulimit -c unlimited     //--
unlimited产生无限大的core文件
ulimit -c 0             //--
数字代表指定大小，0为关闭

2、如果文件系统空间过小，可以考虑将生成core文件保存在nfs或U盘其他存储设备

设置core的路径和格式：
cat
/proc/sys/kernel/core_pattern
core     
注意：core文件默认的存储位置与对应的可执行程序在同一个目录下。

echo
"/mnt/nfs/core.%e.%p.%t"
>
/proc/sys/kernel/core_pattern
注意：这里当前用户必须具有对/proc/sys/kernel/core_pattern的写权限。

这些设置可以在启动脚本中设置，如下：
#
core
dump
debug
#--------------------          
ulimit
-c
unlimited
echo
"/usr/cm/core-%e-%p-%t"
>
/proc/sys/kernel/core_pattern
echo
"core
dump
debug"

编译并运行测试的程序：
gcc
-g
test.c
-o
test
./test

判断一个文件是不是coredump文件
readelf
-h
./core.test.20757.1456447532
//--
详细判断
file
./core.test.20757.1456447532
//--
简单判断

复现程序出现的错误：
gdb
./test
./core.test.20757.1456447532
用bt调出堆栈信息，定位出错信息

//-----------------------------------------------------------------------
场景一：
运行：gdb
./test
./core.test.20757.1456447532
出现："/nfs/test/core-test-3866-1455357791"
is
not
a
core
dump:
不可识别的文件格式         
分析：
1、查看core-test-3866-1455357791文件的大小为0；
2、查看系统限制:
ulimit
-c，出现umlimited
3、在系统目录下运行，可以
4、可能是文件读写权限的限制
5、U盘可以实现了，现在就是NFS权限设置不对了????????





