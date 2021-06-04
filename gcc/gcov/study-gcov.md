study-gcov
==========

## 简介

gcov用来确定代码覆盖,同时我们也可以用它来确认代码被执行了多少次,这在优化过程中非常有用.


## gcov使用

### 用法

### 相关参数









## 运用举例

### 例1

1, 源代码

```c
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

volatile double x;

int main (int argc, char *argv[])
{
    int i;

    for (i = 0;i < 16 * 1000 * 1000; i++) {
        x = 1000.0;

        int r = i & 0xf;

        if (r <= 8) {
            x = pow(x,1.234);
        } else if(r <= 11) {
            x = sqrt(x);
        } else {
            x = 1.0/x;
        }
    }
}
```

2, 编译

```sh
$ gcc -g -O2 -pg -ftest-coverage -fprofile-arcs gcov_test.c -lm -o gcov_test
```
> note: gcov主要使用.gcno和.gcda两个文件,
所以在编译过程中要加入-ftest-coverage和-fprofile-arcs两个参数选项.
-ftest-coverage生成summer-proj.gcno
-fprofile-arcs生成summer-proj.gcda

3，覆盖性测试

```sh
uso@u-os:$ gcov ./gcov_test
File 'gcov_test.c'
Lines executed:100.00% of 9
Creating 'gcov_test.c.gcov'

File '<built-in>'
No executable lines
Removing '<built-in>.gcov'
```

生成文件:

```txt
        -:    0:Source:gcov_test.c
        -:    0:Graph:./gcov_test.gcno
        -:    0:Data:./gcov_test.gcda
        -:    0:Runs:1
        -:    0:Programs:1
        -:    1:#include <stdio.h>
        -:    2:#include <string.h>
        -:    3:#include <stdlib.h>
        -:    4:#include <time.h>
        -:    5:#include <math.h>
        -:    6:
        -:    7:volatile double x;
        -:    8:
        1:    9:int main (int argc, char *argv[])
        -:   10:{
        -:   11:    int i;
        -:   12:
 16000001:   13:    for (i = 0;i < 16 * 1000 * 1000; i++) {
 16000000:   14:        x = 1000.0;
        -:   15:
 16000000:   16:        int r = i & 0xf;
        -:   17:
 16000000:   18:        if (r <= 8) {
  9000000:   19:            x = pow(x,1.234);
  7000000:   20:        } else if(r <= 11) {
  3000000:   21:            x = sqrt(x);
        -:   22:        } else {
  4000000:   23:            x = 1.0/x;
        -:   24:        }
        -:   25:    }
        -:   26:}
```

> note: 我们看到pow(x,1.234)被调用了9000000次,而sqrt(x)被调用了3000000,而1.0/x被调用了4000000.
符合当初程序设计的意图.








