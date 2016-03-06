#include <stdio.h>
#include "misc.h"
#define MAX_NUM 1000000

int main()
{
    int i , next_num, j, length, base, cnt=0,sum=0;
    bool   found_one;
    if(!constrcut_prime_check(MAX_NUM))
        return -1;;

    for(i=10;i<MAX_NUM;i++)
    {
        next_num = i;
        length = check_length(next_num);
        found_one = TRUE;
        for(j=1;j<length;j++)
        {
            base = pow(10,j);
            next_num = i % base;
            if(!check_prime_with_samples(next_num)) {found_one = FALSE; break;}

            base = pow(10,length-j);
            next_num = i / base;
            if(!check_prime_with_samples(next_num)) {found_one = FALSE; break;}

        }
        if(found_one && check_prime_with_samples(i)) 
        {
            cnt ++;
            printf("%2d:%d\n", cnt, i);
            sum += i;
            if(cnt == 11)
                break;
        }
    }

    printf("sum: %d\n", sum);
    deconstruct_prime_check();
    return 0;
    
}

