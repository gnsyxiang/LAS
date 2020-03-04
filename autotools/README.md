autotools
=========

介绍autotools使用

Makefile拥有复杂的语法结构，甚至让人难以领会，当我们项目非常大的时候，维护Makefile会成为一件非常头疼的事情。于是我们就有了autotools工具，专门用来生成Makefile，这个工具让我们很大程度的降低了开发的难度。

Autotools并不是一个工具，而是一系列工具：

* autoscan
 
* aclocal
 
* autoconf
 
* autoheader
 
* automake

记住，这一系列工具看着复杂，最终的目标还是生成Makefile

