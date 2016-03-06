#include <stdio.h>
#include <string.h>
#include "misc.h"

#define MAX_NUM 100000LL

long long triangle_num[MAX_NUM] = {0};

int main()
{

    long long i,j;
    for(i=0;i<MAX_NUM;i++)
    {
        triangle_num[i] = cal_triangle_num(i+1);
        E_PRINTF("%lld\n", triangle_num[i]);
    }

    for(i=285;i<MAX_NUM-1;i++)
        if(is_pentagonal_num(triangle_num[i]) && 
            is_hexagonal_num(triangle_num[i]) ) 
        {
            printf("%lld:%lld\n",i+1, triangle_num[i]);
            return 0;
        }


    return 0;
}

