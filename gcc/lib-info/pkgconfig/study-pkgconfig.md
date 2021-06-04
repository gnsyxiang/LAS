study-pkgconfig
===============


## 简介

使用第三方库，我们在编译、链接的时候，必须指定头文件和库文件的位置。

对于一个比较大第三方库，其头文件和库文件的数量是比较多的。如果我们一个个手动地写，
那将是相当麻烦的。所以，pkg-config就应运而生了。


## 使用

### 参数

### 配置环境变量

* 配置环境变量

    export PKG_CONFIG_PATH=your_pc_path

* 寻找特定的pc文件

    pkg-config --cflags your_lib_name

> note: 以上指定指定了`your_lib_name.pc`，打印出头文件的路径和库文件的路劲


### pc文件书写规范

只需写5个内容即可：Name、Description、Version、Cflags、Libs。

比如简单的:

```txt
Name: haha
Description: haha pc file
Version: 1.0
Cflags:-I/usr/local/include
Libs:-L/usr/local/lib –lxxx –lxxx
```

完整一点:

```txt
# package information for pkg-config

prefix=~/test/skills
include=${prefix}/include
lib=${prefix}/lib
ld_lib=-lxx -lxxx

Name: haha
Description: haha pc file
Version: 1.0
Cflags:-I/${include}
Libs:-L${lib} ${ld_lib}
```

## 实例

### 简单例子

> note: 详细见`pc-demo`，注意在`Makefile`中生成pc文件的方法













