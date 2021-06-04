nvm
===

## 概述

在我们的日常开发中经常会遇到这种情况：手上有好几个项目，每个项目的需求不同，进而不同项目必须依赖不同版的 NodeJS 运行环境。如果没有一个合适的工具，这个问题将非常棘手。

`nvm` 可以切换 `nodejs` 版本

## 安装

* [参考官方链接](https://github.com/creationix/nvm#git-install)

```txt
Git install

If you have git installed (requires git v1.7.10+):

clone this repo in the root of your user profile
cd ~/ from anywhere then git clone https://github.com/nvm-sh/nvm.git .nvm
cd ~/.nvm and check out the latest version with git checkout v0.35.1
activate nvm by sourcing it from your shell: . nvm.sh
Now add these lines to your ~/.bashrc, ~/.profile, or ~/.zshrc file to have it automatically sourced upon login: (you may have to add to more than one of the above files)

export NVM_DIR="$HOME/.nvm"
[ -s "$NVM_DIR/nvm.sh" ] && \. "$NVM_DIR/nvm.sh"  # This loads nvm
[ -s "$NVM_DIR/bash_completion" ] && \. "$NVM_DIR/bash_completion"  # This loads nvm bash_completion 

```

    #apt-get 卸载
    sudo apt-get remove --purge npm
    sudo apt-get remove --purge nodejs
    sudo apt-get remove --purge nodejs-legacy
    sudo apt-get autoremove

    #手动删除 npm 相关目录
    rm -r /usr/local/bin/npm
    rm -r /usr/local/lib/node-moudels
    find / -name npm
    rm -r /tmp/npm*





