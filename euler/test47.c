#include <stdio.h>
#include <string.h>
#include <math.h>
#include "misc.h"




#define MAX_NUM 1000000

#define MAX_PRIMES 100000

#define MAX_FACTOR_CNT 4

int primes[MAX_PRIMES]={0};
int cnt = 0;

int find_factors(int num, int *n, int *factors, int *cnts)
{
    int i=0, j, factors_cnt=0;
    memset(factors, 0, 20*sizeof(int));
    memset(cnts, 0, 20*sizeof(int));
    
    for(;;)
    {
        if(num % primes[i] == 0)
        {
            for(j=0;j<factors_cnt;j++)
            {
                if(factors[j] == primes[i])
                {
                    cnts[j] ++;
                    break;
                }
            }
            if(j == factors_cnt)
            {
                factors[factors_cnt]=primes[i];
                cnts[factors_cnt++]++; 
                if(factors_cnt>MAX_FACTOR_CNT)
                {
                    factors_cnt = 0;/*hack*/
                    break;
                }
            }
            num = num / primes[i];
            if(num == 1)
                break;
        }
        else
        {
            i++;
            if(i > cnt)
                break;
        }
    }
    *n = factors_cnt;
    return factors_cnt;

}

int main()
{
    int num = MAX_NUM, i, j;
    int factor_cnt;
    int factors1[20] = {0},cnts1[20] = {0};
    int factors2[20] = {0},cnts2[20] = {0};
    int factors3[20] = {0},cnts3[20] = {0};
    int factors4[20] = {0},cnts4[20] = {0};
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
    
    for(j=2;j<MAX_NUM-4;j++)
    {
        if(find_factors(j+3, &factor_cnt, factors1 , cnts1) ==MAX_FACTOR_CNT &&
            find_factors(j+2, &factor_cnt, factors2 , cnts2) ==MAX_FACTOR_CNT &&
            find_factors(j+1, &factor_cnt, factors3 , cnts3) ==MAX_FACTOR_CNT &&
            find_factors(j, &factor_cnt, factors4 , cnts4) ==MAX_FACTOR_CNT)
            {
                printf("found %d\n",j);

                printf("%d has %d factors:", j, factor_cnt);
                for(i=0;i<20;i++)
                    if(cnts4[i] >0)
                        printf("%d(%d) ", factors4[i],cnts4[i]);
                printf("\n");            
                
                printf("%d has %d factors:", j+1, factor_cnt);
                for(i=0;i<20;i++)
                    if(cnts3[i] >0)
                        printf("%d(%d) ", factors3[i],cnts3[i]);
                printf("\n");
                
                printf("%d has %d factors:", j+2, factor_cnt);
                for(i=0;i<20;i++)
                    if(cnts2[i] >0)
                        printf("%d(%d) ", factors2[i],cnts2[i]);
                printf("\n");
                
                printf("%d has %d factors:", j+3, factor_cnt);
                for(i=0;i<20;i++)
                    if(cnts1[i] >0)
                        printf("%d(%d) ", factors1[i],cnts1[i]);
                printf("\n");



                break;
            }
    }
    
    deconstruct_prime_check();
    
}


