Linux静态库与动态库制作
=======================

## 静态库

### 特点:

* 把静态库中的相关可执行程序编译到程序中，所用存储空间大  
* 程序的可移植性好  
* 程序升级不方便  
* 所用内存资源较少，因为需要的才会链接  
* 不利于资源的共享，比如相同的代码可能存在很多不同的程序中  


### 创建和使用

* 用-c来生成.o文件  

```sh
  $ gcc -c hello.c
```

* 生成静态库  

```sh
  $ ar rcsv libhello.a hello.o
```

> 注意：库名要以lib开头

* 生成静态库的参数  

* 使用  

```sh
  $ gcc -static world-test.c -L./ -lworld -o world-test
```

> 注意：
> 1) 写库名的时候，将前面的lib去掉，后缀.a也要去掉，前面必须加-l。
> 2) -L 表示链接库文件的位置。
> 3) 声明使用静态库




## 动态库

### 特点:

* 把动态库的版本信息放到程序中，所用存储空间小  
* 移植性不好  
* 程序升级方便  
* 所用内存资源较多，因为要使用库里面的一个函数，必须要加载整个库  
* 很好的资源共享，不同的程序可以共享一个库  

### 动态库的版本号

格式:  
```txt
   libname.so.x.x.x
```
* name是动态库标识名，后面3个x分别表示大版本号，小版本号, 维护号  
* 大版本号: 在改变库里的任何函数接口时才进行改变，接口改变后前面的程序就不能运行了  
* 小版本号: 是不该任何函数接口，只加了几个新的函数，这样前面的程序也能运行  
* 维护号  : 修改函数的bug时才改变  

给动态库设置大版本号:  
```txt
   -Wl,-soname,libname.so.x
```
> 给生成的动态库起别名，其中name和x是可变的

查看动态库大版本号：  

```sh
uso@u-os:$ readelf -d libhello.so

Dynamic section at offset 0xe08 contains 25 entries:
Tag        Type                         Name/Value
0x0000000000000001 (NEEDED)             Shared library: [libc.so.6]
0x000000000000000e (SONAME)             Library soname: [libhello.so.1]
0x000000000000000c (INIT)               0x550
0x000000000000000d (FINI)               0x6b4
0x0000000000000019 (INIT_ARRAY)         0x200df0
0x000000000000001b (INIT_ARRAYSZ)       8 (bytes)
0x000000000000001a (FINI_ARRAY)         0x200df8
0x000000000000001c (FINI_ARRAYSZ)       8 (bytes)
0x000000006ffffef5 (GNU_HASH)           0x1f0
0x0000000000000005 (STRTAB)             0x380
0x0000000000000006 (SYMTAB)             0x230
0x000000000000000a (STRSZ)              188 (bytes)
0x000000000000000b (SYMENT)             24 (bytes)
0x0000000000000003 (PLTGOT)             0x201000
0x0000000000000002 (PLTRELSZ)           24 (bytes)
0x0000000000000014 (PLTREL)             RELA
0x0000000000000017 (JMPREL)             0x538
0x0000000000000007 (RELA)               0x478
0x0000000000000008 (RELASZ)             192 (bytes)
0x0000000000000009 (RELAENT)            24 (bytes)
0x000000006ffffffe (VERNEED)            0x458
0x000000006fffffff (VERNEEDNUM)         1
0x000000006ffffff0 (VERSYM)             0x43c
0x000000006ffffff9 (RELACOUNT)          3
0x0000000000000000 (NULL)               0x0
```


### 创建和使用

* 生成.o文件  

```sh
  $ gcc -fPIC -c hello.c
```

* 生成库  

```sh
  $ gcc -shared hello.o -Wl,soname,libhello.so.x -o libhello.so.x.x.x
```

* 使用  
```sh
  $ gcc -o world-test world-test.c -L./ -lworld
```

### 找动态库和版本兼容

* 在程序链接阶段  
  -lname: 给可执行程序传递个动态库的信息，执行的时候需要这个动态库, 执行`ln -s libname.so libname.so.x.x.x`  
  -L: 指定libname.so所在的目录，而libname.so链接到实际库文件，这就把soname的信息保存在可执行程序中  
  这样执行的时候就会去找soname，同时我们编译时不需要知道实际版本号  

* 在程序执行阶段  
  程序在执行期间，回去找soname这个动态库，但是soname和实际动态库名是不一样的，  
  这时要创建一个软链接来指向实际的动态库, 执行`ls -s libname.so.x libname.so.x.x.x 或 ls -s libname.so.x libname.so (双重链接)`


## 几个注意事项

* 动态库的搜索路径搜索的先后顺序是：  

```txt
  1. 编译目标代码时指定的动态库搜索路径；
  2. 环境变量LD_LIBRARY_PATH指定的动态库搜索路径；
  3. 配置文档/etc/ld.so.conf中指定的动态库搜索路径；
  4. 默认的动态库搜索路径/lib；
  5. 默认的动态库搜索路径/usr/lib.
```

* 查看依赖库

```txt
uso@u-os:$ ldd main
        linux-vdso.so.1 =>  (0x00007ffd00ec9000)
        libhello.so.1 => ./hello-dynamic/libhello.so.1 (0x00007f2959da8000)
        libc.so.6 => /lib/x86_64-linux-gnu/libc.so.6 (0x00007f29599c3000)
        /lib64/ld-linux-x86-64.so.2 (0x000055b541245000)
```

## -L、-rpath和-rpath-link的区别

* -L: 指定`链接时`的库路径  
* LD_LIBRARY_PATH: 指定可执行文件`运行时`库的路径，还指定了库所依赖与其他库的路径  
* -rpath: 指定是`运行时`，程序间接依赖库的库搜索路径，直接编译进可执行程序中  
* -rpath-link: 指的是`链接时`，程序间接依赖库的库搜索路径，只用于链接，不负责运行  

### 测试文件

```c
world.c
#include <stdio.h>

void world(void)
{
    printf("world \n");
}

hello.c
#include <stdio.h>
void world(void);
void hello(void)
{
    printf("hello \n");
    world();
}

test.c
#include <stdio.h>

void main(void)
{
    hello();
}
```

### 生成动态库

```sh
   uso@u-os:$ gcc -c -fPIC world.c
   uso@u-os:$ gcc -shared world.o -o libworld.so

   uso@u-os:$ ldd libworld.so
        linux-vdso.so.1 =>  (0x00007ffe86d30000)
        /lib64/ld-linux-x86-64.so.2.6 => /lib/x86_64-linux-gnu/libc.so.6 (0x00007f923cd24000)
        /lib64/ld-linux-x86-64.so.2 (0x000055bf4123d000)

   uso@u-os:$ gcc -c -fPIC hello.c
   uso@u-os:$ gcc -shared hello.o -o libhello.so

   uso@u-os:$ ldd libhello.so
        linux-vdso.so.1 =>  (0x00007ffce614b000)
        libc.so.6 =>        /lib/x86_64-linux-gnu/libc.so.6 (0x00007f1dfd45e000)
        /lib64/ld-linux-x86-64.so.2 (0x0000563d96eb0000)

```
note: 两个库依赖都是相同的库，并且3个库都是硬编码进libhello.so和libworld.so中。

```sh
   uso@u-os:$ gcc -shared hello.o -lworld -L. -o libhello.so

   uso@u-os:$ ldd libhello.so
        linux-vdso.so.1 =>  (0x00007ffe8c3ee000)
        libworld.sho => not found
        libc.so.6 => /lib/x86_64-linux-gnu/libc.so.6 (0x00007f82f3096000)
        /lib64/ld-linux-x86-64.so.2 (0x000055cd011e1000)
```

note: 此时libhello.so已经依赖于libworld.so，但是没有找到

### 编译test

```sh
   uso@u-os:$ gcc test.c -lhello -L. -o test
   /usr/bin/ld: warning: libworld.so, needed by ./libhello.so, not found (try using -rpath or -rpath-link)
   ./libhello.so: undefined reference to `world'
   collect2: error: ld returned 1 exit status`
```

note: 从上面的现象可以看出，即使用-L指定了路劲，可以找到libhello.so，但是找不到libworld.so。  
虽然它在同一个目录下，但是还是没有办法自动找到libworld.so

```sh
   uso@u-os:$ gcc test.c -lhello -lworld -L. -o test

   uso@u-os:$ ./test
   ./test: error while loading shared libraries: libhello.so: cannot open shared object file: No such file or directory

   uso@u-os:$ ldd test
   linux-vdso.so.1 =>  (0x00007ffc733b2000)
   libhello.so => not foundund
   libc.so.6 => /lib/x86_64-linux-gnu/libc.so.6 (0x00007fa6fa0b8000)
    /lib64/ld-linux-x86-64.so.2 (0x0000560b1d5da000)
```

note: 编译通过了，但是运行找不到库文件路径，可以设置`LD_LIBRARY_PATH`

```sh
   uso@u-os:$ export LD_LIBRARY_PATH=./
   uso@u-os:$ ldd test
        linux-vdso.so.1 =>  (0x00007ffd299e0000)
        libhello.so => ./libhello.so (0x00007efccfed4000)
        libc.so.6 => /lib/x86_64-linux-gnu/libc.so.6 (0x00007efccfaef000)
        libworld.so => ./libworldd.so (0x00007efccf8ec000)
        /lib64/ld-linux-x86-64.so.2 (0x000055e960b0f000)
```

note: -L指定链接时库路径，LD_LIBRARY_PATH指定运行时库路径

### -rpath

```sh
   uso@u-os:$ export LD_LIBRARY_PATH=
   uso@u-os:$ mv libworld.so ./lib
   uso@u-os:$ gcc test.c -lhello -L. -Wl,-rpath ./lib -o test

   uso@u-os:$ ldd test
        linux-vdso.so.1 =>  (0x00007fff6f524000)
        libhello.so => not FINIound
        libc.so.6 => /lib/xFINI_ARRAY
        /lib64/ld-linux-x86-64.so.2 (0x00005600024c6000)

   uso@u-os:$ ./test
        ./test: error while loading shared libraries: libhello.so: cannot open shared object file: No such file or directory

   uso@u-os:$ export LD_LIBRARY_PATH=./
   uso@u-os:$ ./test
```

note: -rpath指的是"运行"时，程序`直接依赖的库的依赖库`去找的目录，  
也就是说，-rpath指定的路径会被记录在生成的可执行程序中，用于运行时。

### -rpath-link

```sh
   uso@u-os:$ export LD_LIBRARY_PATH=
   uso@u-os:$ mv libworld.so ./lib
   uso@u-os:$ gcc test.c -lhello -L. -Wl,-rpath-link ./lib -o test

   uso@u-os:$ ldd test
        linux-vdso.so.1 =>  (0x00007fff6f524000)
        libhello.so => not FINIound
        libc.so.6 => /lib/xFINI_ARRAY
        /lib64/ld-linux-x86-64.so.2 (0x00005600024c6000)

   uso@u-os:$ ./test
        ./test: error while loading shared libraries: libhello.so: cannot open shared object file: No such file or directory

   uso@u-os:$ export LD_LIBRARY_PATH=./
   uso@u-os:$ ./test
        ./test: error while loading shared libraries: libworld.so: cannot open shared object file: No such file or directory

   uso@u-os:$ export LD_LIBRARY_PATH=./:./lib
   uso@u-os:$ ./test
```

note: -rpath-link这个用于"链接"时，例如test依赖libhello.so，但libhello.so又依赖libworld.so，  
-L并没有指定libworld.so的路径，这个时候会从-rpath-link给的路径里找。





















