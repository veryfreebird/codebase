#include <stdio.h>
#include <string.h>
#include <math.h>
#include "misc.h"




#define MAX_NUM 1000000

#define MAX_PRIMES 100000

int primes[MAX_PRIMES]={0};
int cnt = 0;

bool is_matched(int idx, int n, long long *sum_ret)
{
    int i; long long sum=0;
    for(i=0;i<n;i++)
        sum = sum + primes[idx+i];
    if(sum > MAX_NUM)
    {
        *sum_ret = 0;
        return FALSE;
    }        
            
    *sum_ret = sum;
    if(check_prime_with_samples((int)sum))
    {
        return TRUE;
    }
    else
        return FALSE;
}

bool is_matched_with_delta(int idx, int n, long long *sum_ret)
{
    int i; long long sum=0;
    sum = *sum_ret - primes[idx-1] + primes[idx+n-1];
    if(sum > MAX_NUM)
    {
        *sum_ret =0;
        return FALSE;        
    }    
    *sum_ret = sum;
    if(check_prime_with_samples((int)sum))
    {
        return TRUE;
    }
    else
        return FALSE;
}

int main()
{
    int num = MAX_NUM, i, j; long long sum;
    if(!constrcut_prime_check(num))
        return -1;;
    
    for(i=1;i<num;i++)
    {
        if(check_prime_with_samples(i))
        {   
            primes[cnt++] = i;
        }
    }
    
    printf("Found %d primes\n", cnt);
    
    for(j=cnt;j>21;j--)
    {
        printf("%d\n", j);
        if(is_matched(0, j, &sum))
        {
            printf("%d primes sumed from %d, sum: %d\n", j, 0, (int)sum);
            goto end;
        }
        if(sum == 0)
            continue;
    
        for(i=1;i<cnt-j;i++)
        {
            if(is_matched_with_delta(i, j, &sum))
            {
                printf("%d primes sumed from %d, sum: %d\n", j, i, (int)sum);
                goto end;
            }
            if(sum == 0)
                break;
        }
    }
    
end:   
    deconstruct_prime_check();
    
}


