#include <stdio.h>
#include <math.h>
#include <string.h>
#include "misc.h"

int main()
{

    long long i; long long tmp, sum=0;
    for(i=2;i<10000;i++)
    {
        tmp = check_factor_sum((long long)i);
        if(tmp != i && check_factor_sum(tmp) == i)
        {
            printf("%lld - %lld\n", i, tmp);
            sum += i;
         }
    }
    printf("Sum: %lld\n", sum);
    return 1;
}

