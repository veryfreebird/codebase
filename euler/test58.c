#include <stdio.h>

#include "misc.h"

#define MAX_NUM 50000
int main()
{
    int i, j, cnt=1, prime_cnt=0;
    long long num;

    if(!constrcut_prime_check_long(1000000000LL))
        return -1;;

    
    E_PRINTF("%d ", 1);
    for(i=3;i<=MAX_NUM;i+=2)
    {
        for(j=0;j<4;j++)
        {
            num = (i-2)*(i-1)+1+(i-1)*j;
            E_PRINTF("%lld ", num);
            if(j!=3 && check_prime_with_samples_long(num))
                prime_cnt++;
            
        }
        cnt = cnt+4;
        if(prime_cnt*10 < cnt)
        {
            printf("\nmatched, %d\n", i);
            break;
        }
    }
    printf("prime_cnt/cnt: %d/%d=%f\n", prime_cnt, cnt, (float)prime_cnt/(float)cnt);

    deconstruct_prime_check_long();

    
}

