autoscan
========

### 简介

先构建项目目录结构(最好是有demo程序)，在需要导出`Makefile`的目录中建立`Makefile.am`文件，
方便`autoscan`命令生成更完整的配置文件。

在项目根目录下执行`autoscan`命令扫描项目目录，搜寻普通的可移植性问题，比如检查编译器，库，头文件等。
生成`configure.scan`文件后重命名成`configure.ac`，然后编辑配置这个文件，才能继续执行后面的命令。

### 语法规则

```txt
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

| 标签名            | 说明
| -                 | -
|AC_PREREQ          | 声明autoconf要求的版本号
|AC_INIT            | 定义软件名称、版本号、联系方式
|AM_INIT_AUTOMAKE   | 初始化automake，后面的参数直接传递到automake中。foreign 告诉automake这个工程不是标准的GNU项目，有些文件GNU中的必要的文件可以缺失
|AC_CONFIG_SRCDIR   | 宏用来侦测所指定的源码文件是否存在, 来确定源码目录的有效性.。此处为当前目录下main.c。
|AC_CONFIG_HEADERS  | 宏用于生成config.h文件，以便 autoheader 命令使用。
|AC_PROG_CC         | 告诉configure去寻找C编译器，并使用CC编译hello,configure将CC定义成对应编译工具 
|AC_CONFIG_FILES    | 生成相应的Makefile文件，不同文件夹下的Makefile通过空格分隔。
|AC_OUTPUT          | 用来设定 configure 所要产生的文件，如果是makefile，configure 会把它检查出来的结果带入makefile.in文件产生合适的makefile。

 

