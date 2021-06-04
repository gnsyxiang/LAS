/****************************************************************
 * Filename: hello.h
 * -------------------------------
 * Copyright(C),
 * Author: zhenquan.qiu
 * Version: V1.0.0
 * Last modified: 24/08 2017 23:06
 * Description:
 *
 * Change Log:
 * NO.	Author		    Date		Modified
 * 00	zhenquan.qiu	24/08 2017
 ****************************************************************/
#ifndef _HELLO_H_
#define _HELLO_H_

#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifndef HELLO_GB
#define HELLO_EX extern
#else
#define HELLO_EX
#endif

HELLO_EX void hello(void);


#ifdef __cplusplus
}
#endif

#endif /* end _HELLO_H_ */

