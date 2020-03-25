automake
========

### 简介

`automake`工具会根据`configure.in`中的参量把`Makefile.am`转换成`Makefile.in`文件。

### 参数

* `--add-missing`
可以让`automake`自动添加一些必需的脚本文件。如果发现一些文件不存在，可以通过手工`touch`命令创建。

### 语法规则

#### 可执行文件类型

```txt
bin_PROGRAMS  = hello #软件生成后的可执行文件名称为hello
hello_SOURCES = main.c #当前目录源文件，如果当前目录有多个源文件，通过空格进行分隔
hello_LDADD   = src/libpro.a #连接的时候所需的库文件
hello_LDFLAGS = #连接的时候所需库文件的标识
LIBS          = -lpthread -levent
```

| 标签名        | 说明
| -             | -
| bin_PROGRAMS  | 生成的可执行文件名称。如果生成的可执行文件名称为多个，则可以通过空格的方式分隔。<br>bin_PROGRAMS：当运行make install命令的时候，可执行文件会默认安装到linux系统的/usr/local/bin目录下面。<br>noinst_PROGRAMS：如果make install的时候不想被安装，可以使用noinst_PROGRAMS命令。
| hello_SOURCES | 编译成可执行文件所依赖的.c源文件。多个源文件之间用空格分隔。hello为可执行文件名称。
| hello_LDADD   | 编译成可执行文件过程中，连接所需的库文件，包括\*.so的动态库文件和.a的静态库文件。
| hello_LDFLAGS | 连接的时候所需库文件的标识

#### 静态库文件类型

```txt
noinst_LIBRARIES  = libpro.a          #生成的静态库文件名称，noinst加上之后是只编译，不安装到系统中。
libpro_a_SOURCES  = sum.c get.c val.c #这个静态库文件需要用到的源文件。
libpro_a_LDADD    =                   #加载库文件
libpro_a_LDFLAGS  =                   #连接的时候所需库文件的标识
```

| 标签名            | 说明
| -                 | -
| noinst_LIBRARIES  | 生成静态库（\*.a）或者动态库(\*.so)的名称。库文件一般以lib\*.a或者lib\*.so来命名。<br> noinst_LIBRARIES:当运行make install的时候，库文件不会被安装到linux默认的/usr/local/lib目录下。<br> lib_LIBRARIES:当运行make intsall的时候，则会被安装到/usr/local/lib目录下。
| libpro_a_SOURCES  | c的源文件，libpro_a即上面的livpro.a。多个文件用空格分开。
| libpro_a_LDADD    | 加载所需的库文件。
| libpro_a_LDFLAGS  | 编译的时候的连接标识。

> 注意：静态库使用中，需要对configure.ac中加入AC_PROG_RANLIB

#### 动态库文件类型



#### 头文件

| 标签名            | 说明
| -                 | -
|include_HEADERS    | 安装到`--prefix=`指定的目录中

#### 分发(make dist)和安装(make install)

```txt
confdir=${prefix}/conf    #conf为目录名称(需要在源码中创建), dir为每个文件夹变量必须带上
conf_DATA=conf/*          #这个是将conf/目录下的内容安装到confdir目录下
EXTRA_DIST=conf           #在make dist打包的时候也要将扩展文件夹打包进去
```




#### 数据文件


#### 脚本文件


#### 常用变量

| 标签名            | 说明
| -                 | -
| INCLUDES          | 比如链接时需要所需要的头文件
| LDADD             | 比如连接时所需要的库文件
| LDFLAGS           | 比如链接时所需要的库文件选项标志
| EXTRA_DIST        | 源程序和一些默认的文件将自动打入.tar.gz包，其他文件若要进入.tar.gz包可以用这种办法，比如配置文件，数据文件等等
| SUBDIRS           | 在处理本目录前要递归处理哪些子目录
| AUTOMAKE_OPTIONS  | 软件等级  


# bin_PROGRAMS 是需要安装的可执行文件，如果文件不需要安装可以使用 noinst_PROGRAMS
# _PROGRAMS构建文件
# _SCRIPTS 生成脚本
# _DATA 生成数据文件
# _LIBRARIES 生成库文件
# make dist 发布文件时，source文件也会打到发布的文件中

noinst_HEADERS = xxx.h
#这个表示该头文件只是参加可执行文件的编译，而不用安装到安装目录下。如果需要安装到系统中，
#可以用include_HEADERS来代替

xxx_CPPFLAGS = -DCONFIG_DIR=\"$(sysconfdir)\" -DLIBRARY_DIR=\"$(pkglibdir)\"
#xxx_CPPFLAGS 这和Makefile文件中一样，表示C语言预处理参数，这里指定了DCONFIG_DIR，以后
#在程序中，就可以直接使用CONFIG_DIR。不要把这个和另一个CFLAGS混淆，后者表示编译器参数
