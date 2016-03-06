#include <stdio.h>
#include <string.h>
#include "misc.h"

/*
with N set to 200
real    0m5.524s
user    0m5.452s
sys     0m0.062s*/


#define MAX_NUM 100

int main()
{
    int aa[N],bb[N],sum1[N],cc[N],dd[N],sum2[N]; 
    int m, n,i,j,cnt=0;
    for(m=2;m<=MAX_NUM;m++)
        for(n=2;n<m;n++)
        {
            memset(aa,0,N*sizeof(int));
            format_long_num(m,aa);
            memset(cc,0,N*sizeof(int));
            format_long_num(1,cc);

            for(i=0;i<n-1;i++)
            {
                memset(bb,0,N*sizeof(int));
                format_long_num(m-i-1,bb);
                memset(sum1,0,N*sizeof(int));
                mul_long_nums(aa,bb,sum1);
                               
                memset(dd,0,N*sizeof(int));
                format_long_num(i+2,dd);
                memset(sum2,0,N*sizeof(int));
                mul_long_nums(cc,dd,sum2);
                
                memcpy(aa,sum1, N*sizeof(int));
                memcpy(cc,sum2, N*sizeof(int));
            }
            memset(sum2,0,N*sizeof(int));
            memset(dd,0,N*sizeof(int));
            format_long_num(1000000,dd);            
            mul_long_nums(cc,dd,sum2);
            if(compare_long_nums(sum1,sum2) == 1)
            {
                printf("%d,%d\n",m,n);
                cnt++;
            }
#if 0            
            output_long_num(sum1);
            output_long_num(sum2);
#endif            
                    
        }   
    printf("total cnt:%d\n", cnt);          
   
    return 0;
}

