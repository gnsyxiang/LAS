gdb/gdbserver 使用说明
======================

## 编译

> note: 详见makefile


## 使用

### gdbserver

* 编译的gdbserver不需要依赖库文件，经gcc编译后，就可以在对应的平台上运行。

    在开发板上运行：
```sh
    ./gdbserver 200.200.200.2:6666 ./Main
```
> 注意：200.200.200.2：调试主机的IP地址
>       6666：调试主机打开的端口号，该端口一般大于1024



### gdb

* 编译的gdb在host平台下运行，调试target平台下的代码
    在本地主机上运行：

```sh
    ./gdb
    target remote 200.200.200.1:6666
```
> 注意：200.200.200.1：板子的IP地址
>       6666：开启对应的端口
>
> 注意：在生成程序的时候，必须把调试信息加载到可执行文件中。
>       1、CFLAGS += -g
>       2、生成的程序不能用strip去掉调试信息

* 在电脑端执行如下命令

```
$ ./pc-arm-linux-gdb
GNU gdb (GDB) 8.2.1
Copyright (C) 2018 Free Software Foundation, Inc.
License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>
This is free software: you are free to change and redistribute it.
There is NO WARRANTY, to the extent permitted by law.
Type "show copying" and "show warranty" for details.
This GDB was configured as "--host=x86_64-linux-gnu --target=arm-linux".
Type "show configuration" for configuration details.
For bug reporting instructions, please see:
<http://www.gnu.org/software/gdb/bugs/>.
Find the GDB manual and other documentation resources online at:
    <http://www.gnu.org/software/gdb/documentation/>.

For help, type "help".
Type "apropos word" to search for commands related to "word".
(gdb) target remote 192.168.110.14:6666
```

> note: target remote 192.168.110.14:6666

### gdb功能

* 启动你的程序，可以按照你的自定义的要求随心所欲的运行程序

* 可让被调试的程序在你所指定的调置的断点处停住(断点可以是条件表达式)

* 当程序被停住时，可以检查此时你的程序中所发生的事

* 动态的改变你程序的执行环境

### gdb启动方法

* gdb <program> 

  program也就是你的执行文件，一般在当前目录下。

* gdb <program> core

  用gdb同时调试一个运行程序和core文件，core是程序非法执行后core dump后产生的文件。

* gdb <program> <PID>

  如果你的程序是一个服务程序，那么你可以指定这个服务程序运行时的进程ID。gdb会自动attach上去，并调试他。program应该在PATH环境变量中搜索得到。

### 调试开关

* -symbols <file>
  -s <file>                 从指定文件中读取符号表
* -se file                  从指定文件中读取符号表信息，并把他用在可执行文件中。
* -core <file>
  -c <file>                 调试时core dump的core文件。
* -directory <directory>
  -d <directory>            加入一个源文件的搜索路径。默认搜索路径是环境变量中PATH所定义的路径。

### 基本命令

* 在上一次命令后，直接按回车，重复上一个命令

* q/quit/ctrl+d：退出调试

* r/run: 运行程序

浏览历史命令
Ctrl+p: 上一个
Ctrl+n: 下一个

### backtrace使用

一般察看函数运行时堆栈的方法是使用GDB（bt命令）之类的外部调试器,
但是,有些时候为了分析程序的BUG,(主要针对长时间运行程序的分析),在程序出错时打印出函数的调用堆栈是非常有用的。

* bt：查看全部堆栈信息

* frame: 当前的堆栈

* frame num(栈帧编号)

* up: 查看父堆栈

* down: 查看下一个堆栈


### 断点使用

* 设置断点

  break 16：在源码中的第16行
  break func：在函数func()入口处
  info break、infor breakpoints、i b：查看断点信息

* 条件断点

  condition break_p_num (断点编号) cond (条件)

* 临时断点: 在首次到达该指定行后，就不在有效了

  tbreak

* 删除断点：

  delete break_point_num: 可以连续删除多个断点
  delete 删除所有断点

  clear: 清除GDB将执行的下一个指令处的断点
  clear function
  clear filename:function
  clear filename:line_number

* 禁用与启用断点

  disable breakpoint-list: 禁用断点
  disable: 禁用所有现存断点
  
  enable breakpoint-list：启用断点
  enable once breakpoint-list: 在下次引起GDB暂停执行后禁用
  
  finish: 执行完当前所在的函数，但是并不会执行完程序
  
* 断点命令列表
  让GDB在每次到达某个断点时自动执行一组命令，从而自动完成某一任务。
	commands breakpoint_number
	...
	commands
	...
	end

* 

	finish(fin): 使gdb恢复执行，直到恰好在当前帧完成之后为止
	until(u): 在循环后面的第一行代码处暂停(如果循环中有断点，还是会暂定)
	until line_num
	until function
	until filename:line_num
	until filename:function
	程序运行到指定代码处暂停

* 监视点: 指示gdb每当某个表达式改变了值就暂停执行

  watch z(变量名，复杂表达式)
  注意只能监视存在且在作用域内的变量。一旦变量不再存在调用栈的任何帧中，GDB会自动删除监视点。
  GDB实际上是在变量的内存位置改变值时中断。


### 查看源文件

* l/list: 从第一行开始列出源码
* list line1, line2：line1和line2之间的代码
* list linenum: 在linenum前后的代码显示出来
* list +：列出当前行的后面代码执行
* list -: 列出当前行的前面代码执行
* list function
* set listsize count：设置显示代码的函数
* show listsize：显示打印代码的函数

### 查看变量/线程

* 查看变量信息
  p i：打印变量i的值，print命令的简写


### 恢复执行

* 单步执行
	step(s)：单步越过函数
	next(n): 单步进入函数

	后面可以带参数的，表示跳跃的函数

* 无条件恢复程序执行
	continue(c)：知道遇到下一个断点或者程序结束

	后面可以带一个参数，表示要求gdb忽略下面



