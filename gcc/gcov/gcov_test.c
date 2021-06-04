#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

volatile double x;

int main (int argc, char *argv[])
{
    int i;

    for (i = 0;i < 16 * 1000 * 1000; i++) {
        x = 1000.0;

        int r = i & 0xf;

        if (r <= 8) {
            x = pow(x,1.234);
        } else if(r <= 11) {
            x = sqrt(x);
        } else {
            x = 1.0/x;
        }
    }
}
