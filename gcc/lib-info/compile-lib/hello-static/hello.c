/****************************************************************
 * Filename: hello.c
 * -------------------------------
 * Copyright(C),
 * Author: zhenquan.qiu
 * Version: V1.0.0
 * Last modified: 24/08 2017 23:05
 * Description:
 *
 * Change Log:
 * NO.	Author		    Date		Modified
 * 00	zhenquan.qiu	24/08 2017
 ****************************************************************/
#define HELLO_GB
#include "hello.h"
#undef HELLO_GB

void hello(void)
{
    printf("hello world \n");
}

