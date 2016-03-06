#include <stdio.h>
#include <math.h>
#include <string.h>
#include "misc.h"

/*#define N 400
# time ./test
max: i 99 j 95 sum 972
real    0m0.779s
user    0m0.749s
sys     0m0.046s*/



#define MAX_NUM 100

int aa[N],bb[N],cc[N], sum_save[N];
int main()
{
    int i,j, sum_max = 0, sum, m, n;
   
    for(i=1;i<=MAX_NUM;i++)
    {
        memset(aa, 0, sizeof(int)*N);
        format_long_num(i, aa);
        memset(bb, 0, sizeof(int)*N);
        format_long_num(i, bb);
        for(j=1;j<MAX_NUM;j++)
        {
            memset(cc, 0, sizeof(int)*N);
            mul_long_nums(aa,bb,cc);
            memcpy(aa, cc, sizeof(int)*N);  

            sum = sum_long_num_digits(cc);
            if(sum > sum_max)
            {
                sum_max = sum;
                m = i;
                n = j+1;
            }
            
        }
    }
    printf("max: i %d j %d sum %d", m, n, sum_max);
            
    return 0;
}
    

