init_func_table
===============

## 使用方式

```
__attribute__((section("section_name")))
```
作用: 其作用是将作用的函数或数据放入指定名为"section_name"的段。


## demo

### 代码

在代码中，我们做了3件事：

* 使用__attribute__((section()))定义了宏：DECLARE_INIT，此宏把函数放置到初始化函数表

* 使用DELCARE_INIT的宏，声明了3个模块初始化函数：A_init/B_init/C_init

* 在main中通过调用do_initcalls函数，依次调用编译时构建的初始化函数。其中，“_init_start”和“_init_end”的变量在链接脚本中定义。

### 链接脚本

* 获取默认脚本

通过命令`ld --verbose`获取默认链接脚本：

> note: 使用`ld --verbose -m elf_i386`可以指定32平台

```
GNU ld (GNU Binutils for Ubuntu) 2.24

支持的仿真：

elf_x86_64

......

使用内部链接脚本：

==================================================

XXXXXXXX （缺省链接脚本）



==================================================
```
> note: 截取分割线“=====”之间的链接脚本保存为：ldscript.lds

* 自定义数据段

```
_init_start = .;
.myinit : { *(.myinit) }
_init_end = .;
```

> note: “_init_start”和“_init_end”是我们用于识别数据段开始和结束的在链接脚本中定义的变量，
> 而.myinit则是数据段的名称，其中：
> .myinit : { * (.myinit) }：表示.o中的.myinit数据段（输入段）保存到bin中的.myinit数据段（输出段）中

### 编译

* 编译程.o文件并查看信息段

```
gcc -c section.c -o section.o 

$ readelf -S -W section.o 
There are 15 section headers, starting at offset 0x6c8:

Section Headers:
[Nr] Name              Type            Address          Off    Size   ES Flg Lk Inf Al
[ 0]                   NULL            0000000000000000 000000 000000 00      0   0  0
[ 1] .text             PROGBITS        0000000000000000 000040 000090 00  AX  0   0  1
[ 2] .rela.text        RELA            0000000000000000 000490 000108 18   I 13   1  8
[ 3] .data             PROGBITS        0000000000000000 0000d0 000000 00  WA  0   0  1
[ 4] .bss              NOBITS          0000000000000000 0000d0 000000 00  WA  0   0  1
[ 5] .rodata           PROGBITS        0000000000000000 0000d0 000028 00   A  0   0  1
[ 6] .myinit           PROGBITS        0000000000000000 0000f8 000018 00  WA  0   0  8
[ 7] .rela.myinit      RELA            0000000000000000 000598 000048 18   I 13   6  8
[ 8] .comment          PROGBITS        0000000000000000 000110 000035 01  MS  0   0  1
[ 9] .note.GNU-stack   PROGBITS        0000000000000000 000145 000000 00      0   0  1
[10] .eh_frame         PROGBITS        0000000000000000 000148 0000b8 00   A  0   0  8
[11] .rela.eh_frame    RELA            0000000000000000 0005e0 000078 18   I 13  10  8
[12] .shstrtab         STRTAB          0000000000000000 000658 00006e 00      0   0  1
[13] .symtab           SYMTAB          0000000000000000 000200 000228 18     14  13  8
[14] .strtab           STRTAB          0000000000000000 000428 000066 00      0   0  1
Key to Flags:
	W (write), A (alloc), X (execute), M (merge), S (strings), l (large)
	I (info), L (link order), G (group), T (TLS), E (exclude), x (unknown)
O (extra OS processing required) o (OS specific), p (processor specific)
```
> note: 可以看到，段[6]是我们自定义的数据段

### 链接

```
gcc -T ldscript.lds section.o -o section

$ readelf -S -W section
There are 32 section headers, starting at offset 0x1b98:

Section Headers:
[Nr] Name              Type            Address          Off    Size   ES Flg Lk Inf Al
[ 0]                   NULL            0000000000000000 000000 000000 00      0   0  0
[ 1] .interp           PROGBITS        0000000000400238 000238 00001c 00   A  0   0  1
[ 2] .note.ABI-tag     NOTE            0000000000400254 000254 000020 00   A  0   0  4
[ 3] .note.gnu.build-id NOTE            0000000000400274 000274 000024 00   A  0   0  4
[ 4] .gnu.hash         GNU_HASH        0000000000400298 000298 00001c 00   A  5   0  8
[ 5] .dynsym           DYNSYM          00000000004002b8 0002b8 000090 18   A  6   1  8
[ 6] .dynstr           STRTAB          0000000000400348 000348 00004a 00   A  0   0  1
[ 7] .gnu.version      VERSYM          0000000000400392 000392 00000c 02   A  5   0  2
[ 8] .gnu.version_r    VERNEED         00000000004003a0 0003a0 000020 00   A  6   1  8
[ 9] .rela.dyn         RELA            00000000004003c0 0003c0 000018 18   A  5   0  8
[10] .rela.plt         RELA            00000000004003d8 0003d8 000060 18  AI  5  24  8
[11] .init             PROGBITS        0000000000400438 000438 00001a 00  AX  0   0  4
[12] .plt              PROGBITS        0000000000400460 000460 000050 10  AX  0   0 16
[13] .plt.got          PROGBITS        00000000004004b0 0004b0 000008 00  AX  0   0  8
[14] .text             PROGBITS        00000000004004c0 0004c0 000202 00  AX  0   0 16
[15] .fini             PROGBITS        00000000004006c4 0006c4 000009 00  AX  0   0  4
[16] .rodata           PROGBITS        00000000004006d0 0006d0 00002c 00   A  0   0  4
[17] .eh_frame_hdr     PROGBITS        00000000004006fc 0006fc 000054 00   A  0   0  4
[18] .eh_frame         PROGBITS        0000000000400750 000750 000174 00   A  0   0  8
[19] .init_array       INIT_ARRAY      0000000000600e10 000e10 000008 00  WA  0   0  8
[20] .fini_array       FINI_ARRAY      0000000000600e18 000e18 000008 00  WA  0   0  8
[21] .jcr              PROGBITS        0000000000600e20 000e20 000008 00  WA  0   0  8
[22] .dynamic          DYNAMIC         0000000000600e28 000e28 0001d0 10  WA  6   0  8
[23] .got              PROGBITS        0000000000600ff8 000ff8 000008 08  WA  0   0  8
[24] .got.plt          PROGBITS        0000000000601000 001000 000038 08  WA  0   0  8
[25] .data             PROGBITS        0000000000601038 001038 000010 00  WA  0   0  8
[26] .myinit           PROGBITS        0000000000601048 001048 000018 00  WA  0   0  8
[27] .bss              NOBITS          0000000000601060 001060 000008 00  WA  0   0  1
[28] .comment          PROGBITS        0000000000000000 001060 000034 01  MS  0   0  1
[29] .shstrtab         STRTAB          0000000000000000 001a81 000114 00      0   0  1
[30] .symtab           SYMTAB          0000000000000000 001098 000768 18     31  51  8
[31] .strtab           STRTAB          0000000000000000 001800 000281 00      0   0  1
Key to Flags:
	W (write), A (alloc), X (execute), M (merge), S (strings), l (large)
	I (info), L (link order), G (group), T (TLS), E (exclude), x (unknown)
O (extra OS processing required) o (OS specific), p (processor specific)
```
> note: 在我链接成的可执行bin中，在[26]段中存在我们自定义的段

### 执行

```
$ ./section 
init address: 0x601048
A_init
init address: 0x601050
B_init
init address: 0x601058
C_init
```

