#!/bin/sh

set -e
set -x

# 执行检查可更新的软件
sudo apt update

# 先用普通的apt工具安装低版本的node，然后再升级最新
sudo apt install nodejs -y
sudo apt install nodejs-legacy -y
sudo apt install nodejs:i386 -y
sudo apt install npm -y

# 更换淘宝的镜像
sudo npm config set registry https://registry.npm.taobao.org

# 查看下配置是否生效
sudo npm config list

sleep 5

# 安装更新版本的工具N
sudo npm install -g n

# 更新node版本
sudo n stable

sudo npm install -g commitizen

#--------------------------------------------
#### 使用demo

# add commitizen(git cz) to format commits 

# git init
# npm init
# commitizen init cz-conventional-changelog --save --save-exact
# git add .
# git cz


#--------------------------------------------
## 更新版本出错

#$ sudo npm install npm@latest -g
#/usr/local/lib/node_modules/npm/bin/npm-cli.js:84
#      let notifier = require('update-notifier')({pkg})
#      ^^^
#
#SyntaxError: Block-scoped declarations (let, const, function, class) not yet supported outside strict mode
#    at exports.runInThisContext (vm.js:53:16)
#    at Module._compile (module.js:374:25)
#    at Object.Module._extensions..js (module.js:417:10)
#    at Module.load (module.js:344:32)
#    at Function.Module._load (module.js:301:12)
#    at Function.Module.runMain (module.js:442:10)
#    at startup (node.js:136:18)
#    at node.js:966:3

# 解决方案
# 直接把“/usr/local/lib/node_modules/npm”目录删掉即可

