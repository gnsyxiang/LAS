#!/bin/sh

# 执行检查可更新的软件
sudo apt update

# 安装sshd服务
sudo apt install openssh-server -y

# 修改配置文件
sudo sed -i 's/prohibit-password$/yes/' /etc/ssh/sshd_config

# 开启ssh服务开机自启动
sudo update-rc.d ssh defaults

# 启动服务
sudo service sshd start

# 查看状态
sudo service sshd status

