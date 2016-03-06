#include <stdio.h>
#include <math.h>
#include <string.h>

#include "misc.h"

#define MAX_NUM1 1000
#define MAX_NUM2 1000

int main()
{
    int a,b,i;
    int sample;
    for(a=1;a<MAX_NUM1;a++)
        for(b=0;b<MAX_NUM2;b++)
        {
                for(i=0;i<a;i++)
                {
                    sample = i*i + a*i + b;
                    if(sample <=0 || is_prime(sample) == FALSE)
                        break;
                }
                if(i==a)
                    E_PRINTF("%d %d\n", a, b);
                
                for(i=0;i<a;i++)
                {
                    sample = i*i - a*i + b;
                    if(sample <=0 || is_prime(sample) == FALSE)
                        break;
                }
                if(i==a)
                    E_PRINTF("%d %d\n", -a, b);       

                for(i=0;i<a;i++)
                {
                    sample = i*i + a*i - b;
                    if(sample <=0 || is_prime(sample) == FALSE)
                        break;
                }
                if(i==a)
                    E_PRINTF("%d %d\n", a, -b);    

                for(i=0;i<a;i++)
                {
                    sample = i*i - a*i - b;
                    if(sample <=0 || is_prime(sample) == FALSE)
                        break;
                }
                if(i==a)
                    E_PRINTF("%d %d\n", -a, -b);                  
        }
        
}

