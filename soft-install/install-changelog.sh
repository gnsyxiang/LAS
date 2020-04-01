#!/bin/sh

sudo npm install -g conventional-changelog-cli


#---------------------------------------
### 增加到配置脚本中

# add the changelog command in the script

#  $ vim package.json
#  {
#      "scripts": {
#        ...
#          "test": "echo \"Error: no test specified\" && exit 1",
#          "changelog": "conventional-changelog -p angular -i CHANGELOG.md -w -s"
#        ...
#      }
#  }

### 在终端上测试

# $ conventional-changelog -p angular -i CHANGELOG.md -w -s
