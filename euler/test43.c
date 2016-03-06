#include <stdio.h>
#include <string.h>
#include "misc.h"

/*
real    0m0.384s
user    0m0.343s
sys     0m0.062s
*/
#define MAX_NUM 10

int main()
{
    int a[N] ={0}, b[N] ={0},sum[N] ={0};
    unsigned long long tmp1, tmp2; int i,j; bool fail;
    char factor[7] = {2,3,5,7,11,13,17};
    char mm[MAX_NUM] = {1,0,2,3,4,5,6,7,8,9};
    char nn[MAX_NUM] = {1,0,2,3,4,5,6,7,8,9};
    do
    {   
        memcpy(mm,nn,MAX_NUM);
        fail = FALSE;
        
        for(j=0;j<7;j++)
        {
            tmp1 = nn[j+1]*100+nn[j+2]*10+nn[j+3];
            if((tmp1 % factor[j]) !=0)
            {
                fail = TRUE;
                break;
            }
        }
        if(!fail)
        {
            memset(b,0,N*sizeof(int));            
            b[0] = MAX_NUM;
            for(i=0;i<MAX_NUM;i++)
            {
                printf("%d", nn[i]);
                b[i+1] = nn[MAX_NUM - i -1];
            }
            printf("\n");
            
            sum_long_nums(a,b,sum);
            printf("sum->");
            output_long_num(sum);
            
            memcpy(a,sum,N*sizeof(int));         
         }
    }while(find_next_perm(MAX_NUM, mm, nn));
    printf("\nTotal sum:\n");
    output_long_num(sum);
   
    return 0;
}

