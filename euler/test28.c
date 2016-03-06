#include <stdio.h>

#include "misc.h"

#define MAX_NUM 1001
int main()
{
    int i, j, sum = 1, num;
    E_PRINTF("%d ", 1);
    for(i=3;i<=MAX_NUM;i+=2)
    {
        for(j=0;j<4;j++)
        {
            num = (i-2)*(i-1)+1+(i-1)*j;
            sum += num;
            E_PRINTF("%d ", num);
        }            
    }
    printf("\nSum: %d\n", sum);
}

