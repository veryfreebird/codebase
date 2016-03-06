#include <stdio.h>
#include <string.h>
#include "misc.h"

#define MAX_NUM 10000

int main()
{
    int i, j, num[N]={0}, out[N] = {0}, sum[N]={0}, cnt=0;

    for(i=10;i<=MAX_NUM;i++)
    {
        memset(num, 0, N*sizeof(int));
        format_long_num(i, num);
        E_PRINTF("%d::::begin\n",i);
        for(j=0;j<50;j++)
        {
            memset(out, 0, N*sizeof(int));
            reverse_long_num(num, out);
            memset(sum, 0, N*sizeof(int));
            sum_long_nums(num,out,sum);
#if 0            
            output_long_num(num);
            output_long_num(out);
            output_long_num(sum);
#endif
            
            if(is_palindromic_long_num(sum))
                break;
            memcpy(num, sum, N*sizeof(int));

        }
        E_PRINTF("%d::::end\n",i);
        if(j==50)
        {
            printf("%d\n", i);
            cnt++;
        }
        
    }
    printf("Total Lychrel num: %d\n", cnt);
    return 0;
}

