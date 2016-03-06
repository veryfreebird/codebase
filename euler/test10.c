#include <stdio.h>
#include <math.h>
#include "misc.h"


int main()
{
    int num = 2000000, i;long long sum=0;
    int cnt = 0, prime_length = 0; 
    if(!constrcut_prime_check(num))
        return -1;;
    
    for(i=1;i<num;i++)
    {
        if(check_prime_with_samples(i))
        {   
            cnt ++;
            sum += i;
       /*     printf("%d ", i);*/
        }
    }
    deconstruct_prime_check();
    
    printf("\ntotal %d, sum %lld\n", cnt, sum);
}
