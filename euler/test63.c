#include <stdio.h>
#include <math.h>
#include <string.h>
#include "misc.h"

/*#define N 100
Total cnt:49

real    0m0.159s
user    0m0.046s
sys     0m0.094s


*/

#ifndef MAX_NUM
#define MAX_NUM 50
#endif

int aa[N],bb[N],cc[N],sum[N], sum_save[N];
int main()
{
    int i,j,cnt=0;
    
    for(i=1;i<=MAX_NUM;i++)
    {
        format_long_num(i, aa);
        format_long_num(i, bb);
        if(1 == aa[0])
        {
          printf("%2d:%d^1 has 1 digits\n",++cnt, i);
        }   

        for(j=2;j<=MAX_NUM;j++)
        {
            mul_long_nums(aa,bb,cc);
            memcpy(aa, cc, sizeof(int)*N);
            if(j == aa[0])
            {
                printf("%2d:%d^%d has %d digits\n", ++cnt,i, j, j);
            }   
            E_PRINTF("%d^%d:", i, j);
#ifdef PRINT_LOG
            output_long_num(aa);
#endif
        }

    }
    printf("Total cnt:%d\n",cnt);       
    return 0;
}
    

