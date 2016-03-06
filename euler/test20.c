#include <stdio.h>
#include <math.h>
#include <string.h>
#include "misc.h"

int aa[N],bb[N];
int main()
{
    int i, sum=0;
    aa[0]=1;
    aa[1]=1;

    for(i=1;i<=100;i++)
    {
        if(i<10)
        {
            bb[0] = 1;
            bb[1] = i;
        }
        else
        if(i<100)
        {
            bb[0] = 2;
            bb[1] = i%10;
            bb[2] = i/10;
        }
        else
        {
            bb[0] = 3;
            bb[1] = 0;
            bb[2] = 0;
            bb[3] = 1;
        }
        mul_long_nums(aa,bb,aa);
    }

    printf("length:%d\n", aa[0]);

    output_long_num(aa);
    for(i=aa[0];i>=1;i--)
    {
        sum += aa[i];
    }
    printf("Total sum: %d\n", sum);    
}
    

