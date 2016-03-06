#include <stdio.h>
#include <stdlib.h>
#include "misc.h"

#define MAX_NUM 100

#define MAX_NUMS MAX_NUM*MAX_NUM+1

int idx = 0;
int *nums[MAX_NUMS] = {NULL};

void insert_long_num(int *num)
{
    int i;
    if(idx >= MAX_NUMS)
    {
        printf("No enough storage for long nums\n");
        return;
    }
    for(i=0;i<idx;i++)
    {
        if((nums[i][0] == num[0]) && (memcmp(nums[i], num, (num[0]+1)*sizeof(int)) == 0)) /*find one existed*/
            break;
    }
    
    if(i == idx)
    {
        memcpy(nums[idx], num, N*sizeof(int));
        idx++;
    }
}



int main()
{
    int i,j;
    int a[N],b[N],c[N],d[N];
    for(i=0;i<MAX_NUMS;i++)
    {
            nums[i] = malloc(N*sizeof(int));
            if(nums[i] == NULL )
            {
                printf("No enough mem\n");
                return -1;
            }
            
            memset(nums[i], 0, N*sizeof(int));
    }

    for(i=2;i<=MAX_NUM;i++)
    {
        format_long_num(i,a);
        memcpy(c,a,N*sizeof(int));
        for(j=2;j<=MAX_NUM;j++)
        {
            mul_long_nums(c,a,d);
            insert_long_num(d);
            memcpy(c,d,N*sizeof(int));            
            
        }
    }

    printf("Total num: %d\n", idx);
#if 0    
    for(i=0;i<idx;i++)
    {
        output_long_num(nums[i]);
    }
#endif

    for(i=0;i<MAX_NUMS;i++);
    {
            if(nums[i] != NULL)
                free(nums[i]);
    }
    
    return 0;
}

