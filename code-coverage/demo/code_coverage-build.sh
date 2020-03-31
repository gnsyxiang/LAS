#!/usr/bin/env bash


make clean ; make

# 归零所有执行过的产生覆盖率信息的统计文件
lcov -d ./ -z

# 初始化并创建基准数据文件
# -c 捕获，-i初始化，-d应用目录，-o输出文件
lcov -c -i -d ./ -o init.info

./test

# 收集测试文件运行后产生的覆盖率文件
lcov -c -d ./ -o cover.info

# -a 合并文件
lcov -a init.info -a cover.info -o total.info

# --remove 删除统计信息中如下的代码或文件，支持正则
lcov --remove total.info '*/usr/include/*' '*/usr/lib/*' '*/usr/lib64/*' '*/usr/local/include/*' '*/usr/local/lib/*' '*/usr/local/lib64/*' '*/third/*' 'testa.cpp' -o final.info


#通过final.info生成html文件

#如果是git目录，可以获取此次版本的commitID，如果不是，忽略此步
# commitId=$(git log | head -n1 | awk '{print $2}')
# 这里可以带上项目名称和提交ID，如果没有，忽略此步
#genhtml -o cover_report --legend --title "${project_name} commit SHA1:${commitId}" --prefix=${curr_path} final.info
# -o 生成的html及相关文件的目录名称，--legend 简单的统计信息说明
# --title 项目名称，--prefix 将要生成的html文件的路径
genhtml -o cover_report --legend --title "lcov"  --prefix=./ final.info



