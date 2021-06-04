/****************************************************************
 * Filename: visibility_in.h
 * -------------------------------
 * Copyright(C),
 * Author: zhenquan.qiu
 * Version: V1.0.0
 * Last modified: 21/09 2017 19:18
 * Description:
 *
 * Change Log:
 * NO.	Author		    Date		Modified
 * 00	zhenquan.qiu	21/09 2017
 ****************************************************************/
#ifndef _VISIBILITY_IN_H_
#define _VISIBILITY_IN_H_

#ifdef __cplusplus
extern "C" {
#endif

#pragma GCC visibility push(hidden)

void hello_a(void);

#pragma GCC visibility pop

#ifdef __cplusplus
}
#endif

#endif /* end _VISIBILITY_IN_H_ */

