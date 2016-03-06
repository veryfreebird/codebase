#include <stdio.h>

#include "misc.h"

#ifndef TEST
#define MAX_NUM 28123 
#else
#define MAX_NUM 30
#endif

long long samples[7000] =
    { 0};

bool is_perfect_num[MAX_NUM+1] = {FALSE};

int main()
{
    long long sum=0, sum_of_perfect_nums = 0, i, j, perfect_num = 0;
    long long cnt=0;
    for(i=1;i<=MAX_NUM;i++)
    {
        if(check_factor_sum(i) > i)
        {
            samples[cnt] = i;
            cnt++;
            /*printf("%5lld,",cnt, i);*/
        }
    }
    /*mark all the perfect nums less than MAX_NUM*/
    for(i=0;i<cnt;i++)
        for(j=0;j<cnt;j++)
        {
            if(samples[i] + samples[j] <= MAX_NUM)
            {
                is_perfect_num[samples[i] + samples[j]] = TRUE;
            }
        }

    /*sum up all the perfect nums less than MAX_NUM*/
    for(i=0;i<=MAX_NUM;i++)
    {
        if(is_perfect_num[i])
        {
         /*   printf("found: %lld\n", i);*/
            sum_of_perfect_nums += i;
        }
    }

    sum = (MAX_NUM+1)*MAX_NUM/2 - sum_of_perfect_nums ;
    printf("Total sum: %lld\n", sum);
    
    return 1;
}

