/****************************************************************
 * Filename: visibility-test.c
 * -------------------------------
 * Copyright(C),
 * Author: zhenquan.qiu
 * Version: V1.0.0
 * Last modified: 21/09 2017 19:01
 * Description:
 * 
 * Change Log:
 * NO.	Author		    Date		Modified
 * 00	zhenquan.qiu	21/09 2017
 ****************************************************************/
#include <stdio.h>

#include "visibility.h"

void hello_a(void);

int main(int argc, const char *argv[])
{

    hello_b();
    hello_a();

    return 0;
}


