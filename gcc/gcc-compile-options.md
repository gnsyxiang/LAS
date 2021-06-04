gcc编译选项
===========

## 优化等级

优化的目的:  
gcc编译器试图改变程序的结构（在保证变换之后的程序与源程序语义等价的前提之下），  
已达到代码大小最小或运行速度最快

> note: 一般来说，不启用优化产生的程序，能很好的作为gdb调试的代码。


* -O0

关闭所有优化选项，也是CFLAGS或CXXFLAGS中没有设置-O等级时的默认等级，这样就不会优化代码

* -O1

最基本的优化等级，缺省值。编译器会在不花费太多编译时间的前提下，
尽量采用一些优化算法降低代码大小和提高可执行代码的运行速度。

* -O2

这是推荐的优化等级。编译器会试图提高代码性能而不会增大体积和大量占用的编译时间。

> note: 一般情况下使用-O2

* -O3

该选项除了执行-O2所有的优化选项之外，一般都是采取很多向量化算法，  
提高代码的并行执行程度，利用现代CPU中的流水线，Cache等。

> note: 这个选项会提高执行代码的大小，当然会降低目标代码的执行时间。

* -Os

相当于-O2.5，在-O2的基础之上，尽量的降低目标代码的大小，这对于存储容量很小的设备来说非常重要。  
为了降低目标代码大小，一般就是压缩内存中的对齐空白(alignment padding)


## 生成文件关联信息

### 测试文件

demo.h
```c
#ifndef _DEMO_H_
#define _DEMO_H_

#define WORLD "world"

#endif
```

demo.c
```c
#include <stdio.h>

#include "demo.h"

int main(int argc, const char *argv[])
{
    printf("hello %s \n", WORLD);

    return 0;

}
```
### gcc各种依赖选项

* -M

包含目标文件所依赖的所有源代码

```sh
uso@u-os:$ gcc -M demo.c
demo.o: demo.c /usr/include/stdc-predef.h /usr/include/stdio.h \
        /usr/include/features.h /usr/include/x86_64-linux-gnu/sys/cdefs.h \
        /usr/include/x86_64-linux-gnu/bits/wordsize.h \
        /usr/include/x86_64-linux-gnu/gnu/stubs.h \
        /usr/include/x86_64-linux-gnu/gnu/stubs-64.h \
        /usr/lib/gcc/x86_64-linux-gnu/5/include/stddef.h \
        /usr/include/x86_64-linux-gnu/bits/types.h \
        /usr/include/x86_64-linux-gnu/bits/typesizes.h /usr/include/libio.h \
        /usr/include/_G_config.h /usr/include/wchar.h \
        /usr/lib/gcc/x86_64-linux-gnu/5/include/stdarg.h \
        /usr/include/x86_64-linux-gnu/bits/stdio_lim.h \
        /usr/include/x86_64-linux-gnu/bits/sys_errlist.h demo.h
```

* -MM

和`-M`相同，但是忽略由`#include`造成的依赖关系

```sh
uso@u-os:$ gcc -MM demo.c
demo.o: demo.c demo.h
```

* -MMD

和`-MM`相同，但是将输出导入到`*.d`的文件里面

```sh
uso@u-os:$ gcc -MMD demo.c

uso@u-os:$ cat demo.d
demo.o: demo.c demo.h
```

* -MD

和`-MMD`相同，只是导出的内容不一样，内容与`-M`是一样的

```sh
uso@u-os:$ gcc -MD demo.c

uso@u-os:~/test/skills/docs/gcc$ cat demo.d
demo.o: demo.c /usr/include/stdc-predef.h /usr/include/stdio.h \
        /usr/include/features.h /usr/include/x86_64-linux-gnu/sys/cdefs.h \
        /usr/include/x86_64-linux-gnu/bits/wordsize.h \
        /usr/include/x86_64-linux-gnu/gnu/stubs.h \
        /usr/include/x86_64-linux-gnu/gnu/stubs-64.h \
        /usr/lib/gcc/x86_64-linux-gnu/5/include/stddef.h \
        /usr/include/x86_64-linux-gnu/bits/types.h \
        /usr/include/x86_64-linux-gnu/bits/typesizes.h /usr/include/libio.h \
        /usr/include/_G_config.h /usr/include/wchar.h \
        /usr/lib/gcc/x86_64-linux-gnu/5/include/stdarg.h \
        /usr/include/x86_64-linux-gnu/bits/stdio_lim.h \
        /usr/include/x86_64-linux-gnu/bits/sys_errlist.h demo.h
```

* -MF

指定的导出文件名，要配合`-M`或`-MM`使用

> note: `-MF`和`-MMD`, `-MF`和`-MD`混用，会覆盖`-MD`或`-MMD`的功能。

```sh
uso@u-os:$ gcc -MM -MF"test.d" demo.c

uso@u-os:$ cat test.d
demo.o: demo.c demo.h
```

* -MT

指定目标文件名

```sh
uso@u-os:$ gcc -MM -MT"haha.d" demo.c
haha.d: demo.c demo.h

uso@u-os:$ gcc -MM -MT"objs/demo.o" demo.c
objs/demo.o: demo.c demo.h

uso@u-os:$ gcc -MM -MT"haha.d" -MT"demo.o" demo.c
haha.d demo.o: demo.c demo.h
```

