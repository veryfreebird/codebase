#include <stdio.h>
#include <math.h>
int main()
{

    int a, b;

    for(a=1; a<=1000; a++)
        for(b=1;b<(int)((1000-a)/2);b++)
            {
            if(a*a == (1000-a-2*b)*(1000-a))
                {
                printf("a:%d, b:%d, c:%d, a*b*c:%d\n", a, b, (int)sqrt(a*a+b*b), a*b*((int)sqrt(a*a+b*b)));
                break;
                }
            }
    return 0;

}
