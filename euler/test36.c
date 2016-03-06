#include <stdio.h>
#include "misc.h"

#define MAX_NUM 1000000
int main()
{

    int i,sum=0;

    for(i=0;i<MAX_NUM;i++)
        if(is_palindromic_num(i,10) && is_palindromic_num(i,2))
        {
            printf("%d\n", i);
            sum += i;
        }

    printf("sum= %d\n", sum);
    return 0;
}

