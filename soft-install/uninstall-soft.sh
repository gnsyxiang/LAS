#!/bin/sh

# 常规卸载
for i in $@
do
  sudo apt purge $i -y
done

# 清理一些不需要的文件
sudo apt autoremove
sudo apt autoclean

# 删除不需要的配置文件
for i in $@
do
  dpkg -l |grep ^rc|awk '{print $2}' |sudo xargs dpkg -P $i
done

# 更新本地缓存
sudo apt update

