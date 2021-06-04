#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int a(void)
{
    sleep(1);/*调用系统函数进行sleep*/

    return 0;
}

int b(void)
{
    sleep(4);/*调用系统函数进行sleep*/

    return 0;
}

int main(int argc,char **argv)
{
    int iterations;

    if (argc != 2) {
        printf("Usage%s<NoofIterations>\n",argv[0]);
        exit(-1);
    } else
        iterations = atoi(argv[1]);

    printf("Noofiterations=%d\n",iterations);

    while (iterations--) {
        a();
        b();
    }
}

