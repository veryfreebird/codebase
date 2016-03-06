#include <stdio.h>
#include <math.h>
#include <string.h>
#include "misc.h"

/*#define N 20*/

#define MAX_NUM 1000

int aa[N],bb[N],cc[N],sum[N], sum_save[N];
int main()
{
    int i,j;
    memset(aa, 0, sizeof(int)*N);
    memset(bb, 0, sizeof(int)*N);
    memset(cc, 0, sizeof(int)*N);
    memset(sum, 0, sizeof(int)*N);
    
    for(i=1;i<=MAX_NUM;i++)
    {
        format_long_num(i, aa);
        format_long_num(i, bb);
        for(j=1;j<i;j++)
        {
            mul_long_nums(aa,bb,cc);
            cut_long_num(10, cc);
            memcpy(aa, cc, sizeof(int)*N);   
        }
        sum_long_nums(aa, sum, sum_save);
        memcpy(sum, sum_save, sizeof(int)*N);
 
        E_PRINTF("%d:", i);
#ifdef PRINT_LOG
        output_long_num(sum);
#endif
    }
    cut_long_num(10, sum);    
    output_long_num(sum);
            
    return 0;
}
    

