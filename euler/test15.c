#include <stdio.h>
#include <math.h>
#include <string.h>
#include "misc.h"
/*
                                      1
                            .....1........1 
                             1........2........1 
                    .....1........3........3.........1 
                    1........4........6........4.........1 
           .....1........5.......10......10........5.........1 
            1........6.......15......20.....15.........6.........1 
   .....1........7.......21......35......35.......21........7.........1 
    1........8.......28......56......70......56.......28........8.........1 

Sn+1 = (2n)! / (n!)2

S1 = 1; Sn+1 = Sn(4n - 2)/n
Read more: http://wiki.answers.com/Q/What_comes_next_2_6_20_70_252_924
*/


long long find_next_pascal_num(long long one_num, int n)
{

   long long next_num;
   next_num = one_num*(4*n-2)/(n);
   E_PRINTF("%d: %lld\n",n, next_num);
   return next_num; 
}
int main()
{
    long long org= 1,i;

    for(i=1;i<21;i++)
        org = find_next_pascal_num(org, i);
    return 1;
	
    
}
