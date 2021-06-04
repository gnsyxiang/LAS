/**
 * Copyright (C) 2017 xxx Co., Ltd.
 * Release under GPLv2.
 * 
 * @file    hello.h
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
#ifndef _HELLO_H_
#define _HELLO_H_

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

