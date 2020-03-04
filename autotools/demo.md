demo教程
========


## 源码在同一目录


## 源码在不同目录

### 准备目录

```sh
$ mkdir -p demo/include demo/src demo/example
$ cd demo
$ touch include/demo.h src/demo.c example/main.c
$ tree
.
├── example
│   └── main.c
├── include
│   └── demo.h
└── src
    └── demo.c
```

### 准备源码

```c
//demo.h
#ifndef __LIBHAL_INCLUDE_DEMO_H_
#define __LIBHAL_INCLUDE_DEMO_H_

#ifdef __cplusplus
extern "C" {
#endif

void hello_world(void);

#ifdef __cplusplus
}
#endif

#endif // __LIBHAL_INCLUDE_DEMO_H_
```

```c
// demo.c
#include <stdio.h>

void hello_world(void)
{
    printf("hello world\n");
}
```

```c
//main.c
#include <stdio.h>

#include "demo.h"

int main(int argc, const char *argv[])
{
    (void)argc;
    (void)argv;

    hello_world();

    return 0;
}
```

### 创建空的`Makefile.am`文件, 为`autoscan`做准备

```sh
$ touch Makefile.am example/Makefile.am include/Makefile.am src/Makefile.am
```

### 生成`configure.ac`

* 使用autoscan, 生成configure.scan

```sh
$ autoscan
$ ls
autoscan.log  configure.scan  example  include  Makefile.am  src
```

```sh
$ cat configure.scan
#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT([FULL-PACKAGE-NAME], [VERSION], [BUG-REPORT-ADDRESS])
AC_CONFIG_SRCDIR([src/demo.c])
AC_CONFIG_HEADERS([config.h])

# Checks for programs.
AC_PROG_CC

# Checks for libraries.

# Checks for header files.

# Checks for typedefs, structures, and compiler characteristics.

# Checks for library functions.

AC_CONFIG_FILES([Makefile
                 example/Makefile
                 include/Makefile
                 src/Makefile])
AC_OUTPUT
```

* 创建configure.ac文件

把`configure.scan`重新命名为`configure.ac`，并修改后如下: 

```sh
$ cat configure.ac
#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT([libhal], [0.0.1], [gnsyxiang@163.com])
AM_INIT_AUTOMAKE([foreign -Wall -Werror])
AC_CONFIG_SRCDIR([src/demo.c])
AC_CONFIG_HEADERS([config.h])

# Checks for programs.
AC_PROG_CC

# Checks for libraries.

# Checks for header files.

# Checks for typedefs, structures, and compiler characteristics.

# Checks for library functions.

AC_CONFIG_FILES([Makefile
                 example/Makefile
                 include/Makefile
                 src/Makefile])
AC_OUTPUT
```

### 生成`aclocal.m4`文件以及`autom4te.cache`文件夹

```sh
$ aclocal
$ ls
aclocal.m4  autom4te.cache  autoscan.log  configure.ac  example  include Makefile.am  src
```

### 生成`config.h.in`文件

```sh
$ autoheader
$ tree
.
├── aclocal.m4
├── autom4te.cache
│   ├── output.0
│   ├── output.1
│   ├── requests
│   ├── traces.0
│   └── traces.1
├── autoscan.log
├── config.h.in
├── configure.ac
├── example
│   ├── main.c
│   └── Makefile.am
├── include
│   ├── demo.h
│   └── Makefile.am
├── Makefile.am
└── src
    ├── demo.c
    └── Makefile.am
```

### 编写`Makefile.am`

* 顶层`Makefile.am`

```sh
$ cat Makefile.am
SUBDIRS = include src example
```

* src中的`Makefile.am`

```sh
$ cat src/Makefile.am
lib_LTLIBRARIES = libhal.la

AM_CFLAGS = -pipe -W -Wall -Werror -I../include
libhal_la_LDFLAGS = -rdynamic -fPIC
libhal_la_SOURCES = demo.c

all: libhal.la
```

* include中的`Makefile.am`

```sh
$ cat include/Makefile.am
include_HEADERS = demo.h
```

* example中的`Makefile.am`

```sh
$ cat example/Makefile.am
AM_CFLAGS = -pipe -W -Wall -Werror -I../include

bin_PROGRAMS = demo

demo_SOURCES = main.c
demo_LDADD = ../src/.libs/libhal.a
```

### 生成`configure`脚本

```sh
$ autoconf
$ ls
aclocal.m4  autom4te.cache  autoscan.log  config.h.in  configure  configure.ac  configure.scan  example  include  Makefile.am  src
```

### 生成`Makefile.in`

```sh
$ automake --add-missing
configure.ac:11: installing './compile'
configure.ac:6: installing './install-sh'
configure.ac:6: installing './missing'
example/Makefile.am: installing './depcomp'
src/Makefile.am:21: error: Libtool library used but 'LIBTOOL' is undefined
src/Makefile.am:21:   The usual way to define 'LIBTOOL' is to add 'LT_INIT'
src/Makefile.am:21:   to 'configure.ac' and run 'aclocal' and 'autoconf' again.
src/Makefile.am:21:   If 'LT_INIT' is in 'configure.ac', make sure
src/Makefile.am:21:   its definition is in aclocal's search path.
automake: warnings are treated as errors
/usr/share/automake-1.15/am/ltlibrary.am: warning: 'libhal.la': linking libtool libraries using a non-POSIX
/usr/share/automake-1.15/am/ltlibrary.am: archiver requires 'AM_PROG_AR' in 'configure.ac'
src/Makefile.am:21:   while processing Libtool library 'libhal.la'
```

根据上面的提示，重新修改`configure.ac`文件

```sh
cat configure.ac
#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT([libhal], [0.0.1], [gnsyxiang@163.com])
AM_INIT_AUTOMAKE([foreign -Wall -Werror])
AC_CONFIG_SRCDIR([src/demo.c])
AC_CONFIG_HEADERS([config.h])

# Checks for programs.
AC_PROG_CC
AM_PROG_AR
LT_INIT

# Checks for libraries.

# Checks for header files.

# Checks for typedefs, structures, and compiler characteristics.

# Checks for library functions.

AC_CONFIG_FILES([Makefile
                 example/Makefile
                 include/Makefile
                 src/Makefile])
AC_OUTPUT
```

