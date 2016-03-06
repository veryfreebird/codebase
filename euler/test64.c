#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "misc.h"

#ifndef MAX_NUM
#define MAX_NUM 10
#endif

 
bool is_matched(int n)
{
    int m;
    m = sqrt(n);
    if(m*m == n)
        return TRUE;
    else
        return FALSE;
}

int a[N]={0};
int b[N][2]={0};

int get_period_of_fractions(int n)
{
    int idx = 1;
    a[0] = sqrt(n);
    b[0][0] = 1;
    b[0][1] = a[0];
    E_PRINTF("%d %d %d\n", a[0], b[0][0], b[0][1]);

    for(;;)
    {
        b[idx][0] = (n - b[idx-1][1]*b[idx-1][1])/b[idx-1][0];

        a[idx] = (int)floor((b[idx-1][1]+a[0])/b[idx][0]);

        b[idx][1] = a[idx]*b[idx][0] - b[idx-1][1];
 
        E_PRINTF("%d %d %d\n", a[idx], b[idx][0], b[idx][1]);


        if(idx > 1 && (b[idx][0] == b[1][0]) && (b[idx][1] == b[1][1]))
        {
            return idx - 1;
        }
        
        idx++;
        if(idx >= N)
        {
            printf("N=%d is not large enough!!!!\n", N);
            exit(-1);
        }    
    }
}

int main()
{

    int cnt=0,num,D; 
    
    for(D=1;D<=MAX_NUM;D++)
    {
        if(is_matched(D))
            continue;
        num = get_period_of_fractions(D);
        /*printf("d:%d - %d\n", D, num);  */
        if(num%2==1)
            cnt++;
     
    }

    printf("Total %d continued fractions have odd period\n", cnt);  
    

    return 0;
}

