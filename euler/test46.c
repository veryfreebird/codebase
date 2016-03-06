#include <stdio.h>
#include <string.h>
#include <math.h>
#include "misc.h"

bool is_matched(int num)
{
    int i, m, n;
    m = sqrt(num/2)+1;
    for(i=1;i<=m;i++)
    {
        n = num - 2*i*i;
        if(n > 0 && check_prime_with_samples(n))
        {
            E_PRINTF("%d=%d+2*%d^2\n", num, n, i);
            return TRUE;
        }
    }
    return FALSE;
}

int main()
{
    int num = 100000, i;
    if(!constrcut_prime_check(num))
        return -1;;
    
    for(i=2;i<num;i++)
    {
        if(i%2 == 1 && (!check_prime_with_samples(i)))
        {   
            E_PRINTF("%d ", i);
            if(!is_matched(i))
            {
                printf("found: %d\n", i);
                break;
            }
        }
    }
    deconstruct_prime_check();
    
}


