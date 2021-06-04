Describes the GCC compile and link options
==========================================

## 控制符号的可见性 -- Controlling Symbol Visibility

参考: http://blog.csdn.net/delphiwcdj/article/details/45225889

在C语言中，可以使用static关键字限制符号（函数或变量）只对当前的文件可见，即，static对符号的限制在单个文件级别。而共享库（或动态库）可能包含一个或多个文件，如何将符号限制在库文件（模块）的级别，大多数链接器提供了将一个模块的所有符号进行隐藏或导出的方法，但这样对符号的控制会缺乏灵活性，因此，还有一些额外的工作需要我们来处理。

* 编译选项 -- compiler flags  

GCC 4.0 提供了一个新的编译选项，用于设置符号在一个文件中默认的可见性。即，-fvisibility=vis 编译选项，且此值可以取 default 或者 hidden。当设置为 default 时，对于没有显式设置为隐藏的符号则全部设置为导出（visible）；当设置为 hidden 时，对于没有显式设置为导出的符号则全部设置为隐藏（hidden）。如果在编译期间没有指定 -fvisibility 选项，则编译器默认使用 -fvisibility=default ，即，符号全部导出（visible）。

```makefile
CFLAGS += -fvisibility=hidden
```

* 函数可见性属性  

显式指定符号visibility属性的优先级，要高于编译时的 -fvisibility 选项。因此，显式设置符号为 default 属性时，意味着此符号一定是导出的（visible）。visibility属性可以用来设置，函数、变量、模板、C++类。如果一个C++类的visibility属性被设置为 hidden，那么它的成员函数、静态成员变量、编译时期产生的元数据（比如，虚函数表、RTTI信息）也都会被设置为 hidden 属性。

```C
__attribute__((visibility("default"))) void MyFunction1() {}
__attribute__((visibility("hidden"))) void MyFunction2() {}
```

> note: 因此，建议在一个比较大的共享库（动态库）中，编译时使用 -fvisibility=hidden 选项默认隐藏全部符号，而在代码中使用 __attribute__((visibility("default"))) 有选择的显式指定要导出的符号。这样可以极大地减少符号冲突，并且减少动态解析额外符号的成本。

```C
#define EXPORT __attribute__((visibility("default")))
// Always export the following function.
EXPORT int MyFunction1();
```

> note: 使用宏的好处是，方便在不同的平台上移植。

* 编译指示 -- Pragmas  

另一个设置符号可见性的方法是，在 GCC 4.0 中使用新的 pragma 关键字。优点是可以不用单独对每个符号进行设置，而是批量的进行设置。

```C
void f() {  }

#pragma GCC visibility push(default)
   void g() {  }
   void h() {  }
#pragma GCC visibility pop
```

* 限制符号可见的原因 -- Reasons for Limiting Symbol Visibility  

即，尽可能使模块封装的更加内聚，尽可能减少模块间符号的冲突，尽可能减少动态链接时不必要的符号解析。

* 设置符号可见的原因 -- Reasons for Making Symbols Visible  

即，一些场景下还是需要将"某些符号“导出给外部的。"





Export symbol table
