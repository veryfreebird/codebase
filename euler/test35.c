#include <stdio.h>
#include "misc.h"


#define MAX_NUM 1000000
int main()
{

    int i, j,len; int cnt =0;
    bool is_prime_num;

    int next_num;

    if(!constrcut_prime_check(MAX_NUM))
        return -1;;
    
    for(j=1;j<MAX_NUM;j++)
    {
        next_num = j;
        len = check_length(next_num);
        is_prime_num = TRUE;
        for(i=0;i<len;i++)
        {
            next_num = next_circular_num(next_num, len);
            if(check_prime_with_samples(next_num) == FALSE) {is_prime_num = FALSE; break;}
        }
        if(is_prime_num)
        {
            printf("%d\n", j);
            cnt ++;
        }
    }

    printf("cnt = %d\n", cnt);
    deconstruct_prime_check();
    return 0;
}

