# stack-protector

在gcc中，通过编译选项可以添加 函数栈的保护机制，通过重新对局部变量进行布局来实现，达到监测函数栈是否非破坏的目的。

gcc中有3个与堆栈保护相关的编译选项

* -fstack-protector：启用堆栈保护，不过只为局部变量中含有 char 数组的函数插入保护代码。
* -fstack-protector-all：启用堆栈保护，为所有函数插入保护代码。
* -fno-stack-protector：禁用堆栈保护。

```c
#include <stdio.h>

int main(void)
{
    int i;
    int a[4];
    // int i;

    printf("&a=%p,&i=%p\n",&a,&i);

    printf("%d\n", a[4]);
    for(i=0;i<=3;i++) /* 当把3改为4的话，程序运行就会出错，因为开启了堆栈保护，在a[4]的地方编译器放置了一个保护变量，当该变量被修改时，程序
                       * 认为该函数栈被破坏，于是抛出错误 */
        a[i]=0;

    printf("hello\n");
    return 0;	
}
```

> 在-fstack-protector-all的编译选项下，编译器会对局部变量的组织方式进行重新布局，
> 在本例中，无论i和a变量的声明前后顺序怎么样，a数组始终在高地址，变量i始终在低地址。
> 并且在a[4]的地址位置，编译器会放置一个保护变量，当该变量被修改时会抛出错误。

