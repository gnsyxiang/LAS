/**
 * Copyright (C) 2017 xxx Co., Ltd.
 * Release under GPLv2.
 * 
 * @file    hello.c
 * @brief   
 * @author  gnsyxiang <gnsyxiang@163.com>
 * @date    04/01 2018 14:24
 * @version v0.0.1
 * 
 * @since    note
 * @note     note
 * 
 *     change log:
 *     NO.     Author              Date            Modified
 *     00      zhenquan.qiu        04/01 2018      create the file
 * 
 *     last modified: 04/01 2018 14:24
 */
#include <stdio.h>

#define HELLO_GB
#include "hello.h"
#undef HELLO_GB

void hello(void)
{
    printf("hello world \n");
}

