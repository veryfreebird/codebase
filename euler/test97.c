#include <stdio.h>
#include <math.h>
#include <string.h>
#include "misc.h"

/*#define N 20*/
#ifndef MAX_NUM
#define MAX_NUM 1000
#endif

int two[N],bb[N],cc[N],tmp[N],sum[N], sum_save[N];
int main()
{
    int i,j;
    memset(two, 0, sizeof(int)*N);
    memset(bb, 0, sizeof(int)*N);
    memset(cc, 0, sizeof(int)*N);
    memset(sum, 0, sizeof(int)*N);
    
    format_long_num(2, two);
    format_long_num(1, bb);
    format_long_num(28433, tmp);    
    for(i=1;i<=MAX_NUM;i++)
    {
        mul_long_nums(bb,two,cc);
        cut_long_num(10,cc);
        memcpy(bb, cc, sizeof(int)*N);  

    }

    mul_long_nums(bb,tmp,cc);
    cut_long_num(10,cc);

    format_long_num(1, bb);    
    sum_long_nums(cc, bb, sum);
    cut_long_num(10,sum);

    output_long_num(sum);
            
    return 0;
}
    

