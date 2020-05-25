objdump
=======

## 常用参数

* objdump -d <file(s)>: 将代码段反汇编；
* objdump -S <file(s)>: 将代码段反汇编的同时，将反汇编代码与源代码交替显示，编译时需要使用-g参数，即需要调试信息；
* objdump -l <file(s)>: 反汇编代码中插入文件名和行号
* objdump -C <file(s)>: 将C++符号名逆向解析
* objdump -j section <file(s)>: 仅反汇编指定的section



