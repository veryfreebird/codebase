#include <stdio.h>
#include <string.h>
#include <math.h>
#include "misc.h"

/*
matched:13 5197 5701 6733 8389, sum:26033

real    0m2.813s
user    0m2.655s
sys     0m0.124s


*/


#define MAX_NUM 100000000

#define MAX_PRIMES 10000

int primes[MAX_PRIMES]={0};
int cnt = 0;

bool check_nums(int i, int j)
{
    int p;
    p = cat_int_num(primes[i],primes[j]);
    return check_prime_with_samples(p);  
}

int main()
{
    int num = MAX_PRIMES, ii, jj,p1,p2; int sum;
    int i[5];
    
    if(!constrcut_prime_check(MAX_NUM))
        return -1;;
    
    for(ii=1;ii<num;ii++)
    {
        if(check_prime_with_samples(ii))
        {   
        
            primes[cnt++] = ii;
            printf("%d ", ii);
        }
    }
    
    printf("\nFound %d primes\n", cnt);
#if 1    
    for(i[0]=0;i[0]<cnt;i[0]++)
    {
        for(i[1]=i[0]+1;i[1]<cnt;i[1]++)
        {
                if(!check_nums(i[1],i[0]) || !check_nums(i[0],i[1]))
                    continue;
                for(i[2]=i[1]+1;i[2]<cnt;i[2]++)
                {
                        if(!check_nums(i[2],i[0]) || !check_nums(i[2],i[1]) 
                        || !check_nums(i[0],i[2]) || !check_nums(i[1],i[2]) )
                            continue;

                        for(i[3]=i[2]+1;i[3]<cnt;i[3]++)
                        {
                            if(!check_nums(i[3],i[0]) || !check_nums(i[3],i[1]) || !check_nums(i[3],i[2]) 
                            || !check_nums(i[0],i[3]) || !check_nums(i[1],i[3]) || !check_nums(i[2],i[3]))
                                continue;

                            for(i[4]=i[3]+1;i[4]<cnt;i[4]++)
                            {

                                printf("%d %d %d %d %d\n",primes[i[0]],primes[i[1]],
                                    primes[i[2]],primes[i[3]],primes[i[4]]);

                                if(!check_nums(i[4],i[0]) || !check_nums(i[4],i[1]) || !check_nums(i[4],i[2]) || !check_nums(i[4],i[3])  
                                || !check_nums(i[0],i[4]) || !check_nums(i[1],i[4]) || !check_nums(i[2],i[4]) || !check_nums(i[3],i[4]))
                                    continue;
                                    
                                sum = primes[i[0]]+primes[i[1]]+primes[i[2]]+primes[i[3]]+primes[i[4]];
                                printf("matched:%d %d %d %d %d, sum:%d\n",primes[i[0]],primes[i[1]],
                                primes[i[2]],primes[i[3]],primes[i[4]],sum);
                                                                
                                goto end;

                            }
                    }
            }
        }
    }
#endif
end:
    deconstruct_prime_check();
    
}


