autotools
=========

### 介绍autotools使用

`Makefile`拥有复杂的语法结构，甚至让人难以领会，当我们项目非常大的时候，
维护`Makefile`会成为一件非常头疼的事情。于是我们就有了`autotools`工具，
专门用来生成`Makefile`，这个工具让我们很大程度的降低了开发的难度。

`autotools`并不是一个工具，而是一系列工具：

* autoscan
 
* aclocal
 
* autoheader
 
* automake

* autoconf

这一系列工具看着复杂，最终的目标还是生成`Makefile`

### 生成`aclocal.m4`

1.autoscan (autoconf): 扫描源代码以搜寻普通的可移植性问题，比如检查编译器，库，头文件等，
  生成文件`configure.scan`，它是`configure.ac`的一个雏形。

2.aclocal (automake): 根据已经安装的宏，用户定义宏和`acinclude.m4`文件中的宏将`configure.ac`文件所需要的宏集中定义到文件`aclocal.m4`中。
`aclocal`是一个perl 脚本程序，它的定义是：“aclocal - create aclocal.m4 by scanning configure.ac”

```txt
user input files   optional input     process          output files
================   ==============     =======          ============
                    acinclude.m4 - - - - -.
                                          V
                                      .-------,
configure.ac ------------------------>|aclocal|
                 {user macro files} ->|       |------> aclocal.m4
                                      `-------'
```                

### 生成`autoconfig.h.in`

3.autoheader(autoconf): 根据`configure.ac`中的某些宏，比如cpp宏定义，运行m4，生成`config.h.in`

```txt
user input files    optional input     process          output files
================    ==============     =======          ============
                    aclocal.m4 - - - - - - - .
                                             |
                                             V
                                     .----------,
configure.ac ----------------------->|autoheader|----> autoconfig.h.in
                                     `----------'
```

### 生成`Makefile.in`

4.automake: automake将Makefile.am中定义的结构建立Makefile.in，然后configure脚本将生成的Makefile.in文件转换为Makefile。
如果在configure.ac中定义了一些特殊的宏，比如AC_PROG_LIBTOOL，它会调用libtoolize，否则它会自己产生config.guess和config.sub

```txt
user input files   optional input   processes          output files
================   ==============   =========          ============
                                     .--------,
                                     |        | - - -> COPYING
                                     |        | - - -> INSTALL
                                     |        |------> install-sh
                                     |        |------> missing
                                     |automake|------> mkinstalldirs
configure.ac ----------------------->|        |
Makefile.am  ----------------------->|        |------> Makefile.in
                                     |        |------> stamp-h.in
                                 .---+        | - - -> config.guess
                                 |   |        | - - -> config.sub
                                 |   `------+-'
                                 |          | - - - -> config.guess
                                 |libtoolize| - - - -> config.sub
                                 |          |--------> ltmain.sh
                                 |          |--------> ltconfig
                                 `----------'
```

### 生成`configure/Makefile`

5.autoconf:将configure.ac中的宏展开，生成configure脚本。这个过程可能要用到aclocal.m4中定义的宏。

```txt
user input files   optional input   processes          output files
================   ==============   =========          ============
                   aclocal.m4 - - - - - -.
                                         V
                                     .--------,
configure.ac ----------------------->|autoconf|------> configure ----->autoconfig.h,Makefile
```

引用：

https://www.laruence.com/2008/11/11/606.html
