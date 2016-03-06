#include <stdio.h>
#include "misc.h"

int nums[10]={1};
    
#define MAX_NUM 10000000LL

bool check_num(long long num)
{
    long long tmp, sum=0;
    tmp = num;
    for(;;)
    {
        if(tmp ==0)
            break;
        sum += nums[tmp % 10];
        tmp = tmp / 10;        
    }
    if(sum == num)
    {
        printf("%d\n", num);
        return TRUE;
    }
    else
        return FALSE;
}

    
int main()
{
    

    int i; long long j=1;
    nums[1] = 1;
    for(i=2;i<10;i++)
        nums[i] = nums[i-1]*i;
        
    for(j=3;j<MAX_NUM;j++) 
        check_num(j);    
                     
    return 0;
}