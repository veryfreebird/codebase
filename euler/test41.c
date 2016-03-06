#include <stdio.h>
#include "misc.h"

#define MAX_NUM 7654321

/*
real    0m29.679s
user    0m28.858s
sys     0m0.030s


*/

int main()
{
    int i, len;
    if(!constrcut_prime_check(MAX_NUM))
        return -1;;
    
    for(i=2;i <= MAX_NUM;i++)
    {
        len = check_length(i);
        if(is_n_pandigital_num(len, i) && check_prime_with_samples(i))
            printf("%d\n",i);
    }


    deconstruct_prime_check();
    
    return 0;
}

