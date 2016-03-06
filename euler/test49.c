#include <stdio.h>
#include <string.h>
#include <math.h>
#include "misc.h"


bool find_num(int n, int *list, int length)
{
    int i=0;
    for(i=0; i< length; i++)
    {
        if(n == list[i])
            return TRUE;
        if(n< list[i])
            return FALSE;
    }
    return FALSE;
    
}

void sort_list(int *list, int len)
{
    int i,l,tmp;
    for(i=0;i<=len-2;i++)
        for(l=i+1;l<=len-1;l++)
            if(list[i] > list[l])
            {
                tmp = list[i];
                list[i] = list[l];
                list[l] = tmp;
            }
}

#define MAX_NUM 1000000

#define MAX_PRIMES 100000

#define MAX_FACTOR_CNT 4

int primes[MAX_PRIMES]={0};
int cnt = 0;


int main()
{
    int num = MAX_NUM, i, j,tmp;
    int a[N],b[N],c[N];
    if(!constrcut_prime_check(num))
        return -1;;
    
    for(i=1000;i<9999;i++)
    {
        if(check_prime_with_samples(i))
        {
#if 0        
            format_long_num(i, a);
            if(a[1] != a[2] && a[1] != a[3] && a[1] != a[4] &&
                                      a[2] !=a[3] && a[2] != a[4] &&
                                                           a[3] != a[4])
#endif                                                           
            {
                primes[cnt++] = i;
            }
        }
    }
    
    printf("Found %d primes\n", cnt);

    for(i=0;i<cnt-2;i++)
        for(j=i+2;j<cnt;j++)
        {
            tmp = primes[i] + primes[j];
            if(tmp %2 ==0 && find_num(tmp/2,primes, cnt))
            {
                
                format_long_num(primes[i], a);
                sort_list(&a[1],4);
                format_long_num(tmp/2, b);
                sort_list(&b[1],4);                
                format_long_num(primes[j], c);
                sort_list(&c[1],4);                 
                if(memcmp(a,b,5*sizeof(int)) ==0 && memcmp(b,c,5*sizeof(int)) ==0)
                    printf("%d %d %d\n", primes[i], tmp/2, primes[j]);
            }
        }
    
    deconstruct_prime_check();
    
}


