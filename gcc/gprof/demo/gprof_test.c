#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>

int fast_multiply(int x,  int y)
{
    return x * y;
}

int slow_multiply(int x, int y)
{
    int i, j, z;
    for (i = 0, z = 0; i < x; i++)
        z = z + y;
    return z;
}

int main (int argc, char *argv[])
{
    int i, j;
    int a, b;

    for (i = 0;i < 300; i++){
        for (j = 0; j < 10 * 1000; j++){
            a = fast_multiply(i, j);
            b = slow_multiply(i, j);
        }
    }

    printf("a=%d, b=%d\n", a, b);

    return 0;
}
