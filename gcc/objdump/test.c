/**
 * 
 * Release under GPL-3.0.
 * 
 * @file    test.c
 * @brief   
 * @author  gnsyxiang <gnsyxiang@163.com>
 * @date    25/05 2020 10:26
 * @version v0.0.1
 * 
 * @since    note
 * @note     note
 * 
 *     change log:
 *     NO.     Author              Date            Modified
 *     00      zhenquan.qiu        25/05 2020      create the file
 * 
 *     last modified: 25/05 2020 10:26
 */
#include <stdio.h>

void swap(int *first, int *second)
{
    int temp = *first;
    *first   = *second;
    *second  = temp;
}

int main(int argc, const char *argv[])
{
    (void)argc;
    (void)argv;

    int a = 10;
    int b = 20;

    printf("a = %d; b = %d;\n", a, b);
    swap(&a, &b);
    printf("a = %d; b = %d;\n", a, b);

    return 0;
}
