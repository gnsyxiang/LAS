gcov
====

### 简介

首先我们要了解什么是gcov，gcov伴随gcc 发布。

gcov是一个测试代码覆盖率的程序，正确地使用它搭配GCC可以分析、帮助你将代码写得更高效。帮助你优化程序。类似于一个profiling tool，使用gcov或者gprof，可以收集到一些基础的性能统计数据。比如：

* 每一行代码执行的频度

* 每个代码文件中实际被执行到的行数

* 每一个代码块执行使用的时间

gcov主要使用.gcno和.gcda两个文件。
* .gcno是由`-ftest-coverage`产生的，它包含了重建基本块图和相应的块的源码的行号的信息。

* .gcda是由加了`-fprofile-arcs`编译参数的编译后的文件运行所产生的，它包含了弧跳变的次数和其他的概要信息（而gcda只能在程序运行完毕后才能产生的）。

gcov创建一个logfile叫做 源文件名称.gcxx (这里的源文件名称指的是.c或者.cc文件的文件名)，表示的是这个 源文件.c 中每一行所被执行的次数。这些文件可以配合gprof使用。

gcov要工作只能用gcc编译这些代码。和其他的profiling 或者 测试代码覆盖率的机制不兼容。

> fprofile-arcs参数使gcc创建一个程序的流图，之后找到适合图的生成树。只有不在生成树中的弧被操纵（instrumented）：gcc添加了代码来清点这些弧执行的次数。当这段弧是一个块的唯一出口或入口时，操纵工具代码（instrumentation code)将会添加到块中，否则创建一个基础块来包含操纵工具代码。

Gcov执行函数覆盖、语句覆盖和分支覆盖。

### 编译程序

* 编译程序时，加入`-fprofile-arcs -ftest-coverage`

* 链接程序时，加入`-lgcov`
















链接：https://www.jianshu.com/p/a42bbd9de1b7




