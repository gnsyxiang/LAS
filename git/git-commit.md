# git commit


<!-- vim-markdown-toc GFM -->

* [代码提交书写规范](#代码提交书写规范)
    + [feat](#feat)
    + [fix](#fix)
    + [refactor](#refactor)
    + [perf](#perf)
    + [test](#test)
    + [doc](#doc)
    + [style](#style)
    + [build](#build)
    + [ci](#ci)
    + [chore](#chore)
    + [revert](#revert)
    + [merge](#merge)
    + [sync](#sync)

<!-- vim-markdown-toc -->


## 代码提交书写规范

#### feat

功能feature的意思，也是最常用的。当你的功能有变更的时候，都可以采用这种类型的type

#### fix

当然指的是bug修复，最后要带上bug编号，如(#33)

#### refactor

重构代码。指的是代码结构的调整，比如使用了一些设计模式重新组织了代码

#### perf

对项目或者模块进行了性能优化。比如一些jvm的参数改动，把stringbuffer改为stringbuilder等

#### test

这个简单，就是增加了单元测试和自动化相关的代码

#### doc

更新了文档，或者更新了注释

#### style

代码格式调整，比如执行了format、更改了tab显示等

#### build

影响编译的一些更改，比如更改了maven插件、增加了npm的过程等

构建工具或构建过程等的变动，如：关联包升级等

#### ci

持续集成方面的更改。现在有些build系统喜欢把ci功能使用yml描述。如有这种更改，建议使用ci

#### chore

其他改动。比如一些注释修改或者文件清理。不影响src和test代码文件的，都可以放在这里

#### revert

回滚了一些前面的代码

#### merge

代码合并

#### sync

同步主线或分支的Bug

