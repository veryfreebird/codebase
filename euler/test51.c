#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "misc.h"

/*
make -e t=51 m=1000000 n=20
# time ./test
Found 78498 primes
found matched num
0:121313
1:222323
2:323333
3:424343
4:525353
5:626363
6:828383
7:929393

real    0m0.514s
user    0m0.358s
sys     0m0.077s




*/

#ifndef MAX_NUM
#define MAX_NUM 100000
#endif

#define MAX_PRIMES 10000000

int primes[MAX_PRIMES]={0};
int cnt = 0;

int temp1[N];

int found_num[10];

bool is_matched(int *num, int n)
{
    int i,j,l,k,matched, ttt;
    for(i=1;i<=num[0]-2;i++)
        for(j=i+1;j<=num[0]-1;j++)
            for(l=j+1;l<=num[0];l++)            
        {
            if(num[i] == num[j] && num[j] == num[l])
            {
                memcpy(temp1,num,N*sizeof(int));
                matched = 0;
                for(k=num[l]+1;k<=9;k++)
                {
                    /*if(k==num[i])
                        continue;*/
                    temp1[i] = k;
                    temp1[j] = k;
                    temp1[l] = k;
                    if(temp1[temp1[0]] == 0)
                        continue; /*the largest digit should not be zero*/
                    ttt = cal_long_num(temp1);
                    if(check_prime_with_samples(ttt))
                    {
                        matched++;
                        found_num[matched] = ttt;
                        if(matched == n-1)
                        {
                            ttt = cal_long_num(num);
                            found_num[0] = ttt;
                            return TRUE;
                        }
                    }
                }
            }
        }
    return FALSE;
}


int temp[N];

int main()
{
    int num = MAX_NUM, i, j;
    if(!constrcut_prime_check(num))
        return -1;;
    
    for(i=1;i<num;i++)
    {
        if(check_prime_with_samples(i))
        {   
            primes[cnt++] = i;
            E_PRINTF("%10d:%d\n", cnt, i);
        }
        if(cnt>=MAX_PRIMES)
        {
            printf("No free space for new prime\n");
            exit(-1);
        }
    }
    
    printf("Found %d primes\n", cnt);

    for(i=0;i<cnt;i++)
    {
        E_PRINTF("%d\n", i);
        format_long_num(primes[i],temp);
        if(is_matched(temp,8))
        {
            printf("found matched num\n");
            for(j=0;j<8;j++)
                printf("%d:%d\n",j,found_num[j]);
            break;
        }
        
    }
    deconstruct_prime_check();
    
}


