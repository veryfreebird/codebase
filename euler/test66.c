#include <stdio.h>
#include <string.h>
#include <math.h>
#include "misc.h"

#ifndef MAX_NUM
#define MAX_NUM 1000
#endif

/*
Pell Equation

make -e t=66 m=1000 n=100 d=t


max d:661
x:
38:16421658242965910275055840472270471049
y:
36:638728478116949861246791167518480580

real    0m3.413s
user    0m0.515s
sys     0m0.046s

*/

typedef struct _PellAns
{
  int p[N],q[N];
} PellAns;
typedef struct _Node
{
  long long g,h;
} Node;


int x[N], y[N], dd[N], one[N];
int result1[N], result2[N];
bool is_matched_long(PellAns *s,int n)
{
  /*  E_PRINTF("%30lld, %30lld\n", s.p, s.q);*/
#if 1
    mul_long_nums(s->q,s->q,result2);
    mul_long_nums(result2, dd, result1);
    sum_long_nums(result1, one, result2);
    
    mul_long_nums(s->p,s->p,result1);
    
    if(compare_long_nums(result1, result2) == 0)
        return TRUE;
    else
        return FALSE;
#endif
#if 0
    if(s.p*s.p - n*s.q*s.q == 1) 
        return TRUE;
    else
        return FALSE;
#endif   
}

int tmp1[N],tmp2[N],aa[N];
PellAns s[4];

void Solve( int n, PellAns *out)
{
    
    Node w[4]; 
    long long a[4];

    format_long_num(n, dd);
/*
    s[0].p=0; s[0].q=1;
    s[1].p=1; s[1].q=0;
    */
    format_long_num(0, s[0].p);
    format_long_num(1, s[0].q);
    format_long_num(1, s[1].p);
    format_long_num(0, s[1].q);    

    a[0]=(int)floor(sqrt( (double)n ));
    a[2]=a[0];
    w[1].g=0;w[1].h=1;
    while( 1 )
    {
        w[2].g = -w[1].g+a[2]*w[1].h;
        w[2].h = (n-w[2].g*w[2].g)/w[1].h;
        a[3] = (int)floor( (double)(w[2].g+a[0])/w[2].h );
/*
        s[2].p = a[2]*s[1].p+s[0].p;
        s[2].q = a[2]*s[1].q+s[0].q;
*/
        format_long_long_num(a[2],aa);

        mul_long_nums(aa, s[1].p,tmp1);
        sum_long_nums(tmp1,s[0].p,s[2].p);

        mul_long_nums(aa, s[1].q,tmp1);        
        sum_long_nums(tmp1,s[0].q,s[2].q);
/*
        printf("p:");
        output_long_num(s[2].p);
        printf("q:");
        output_long_num(s[2].q);        
*/
        if(/*s[2].p>0&& s[2].q>0 && */is_matched_long(&s[2],n))
        {
            memcpy(out,&s[2],sizeof(PellAns));
            return;
        }

        w[0]=w[1];w[1]=w[2];
        a[2]=a[3];

        /*
        s[0]=s[1];s[1]=s[2];*/
        memcpy(&s[0],&s[1],sizeof(PellAns));
        memcpy(&s[1],&s[2],sizeof(PellAns));
    }
}

bool is_matched(int n)
{
    int m;
    m = sqrt(n);
    if(m*m == n)
        return TRUE;
    else
        return FALSE;
}

int main()
{

    long long max_x[N],max_y[N]; int max_D,D; 
    PellAns ans;
    format_long_num(1, one);    
    for(D=1;D<=MAX_NUM;D++)
    {
        if(is_matched(D))
            continue;
        printf("d:%d\n", D);        
        Solve(D, &ans);
        
        if(compare_long_nums(ans.p, max_x) > 0 )
        {
            memcpy(max_x, ans.p,N*sizeof(int));
            max_D = D;
            memcpy(max_y, ans.q,N*sizeof(int));
        }            
    }

    printf("max d:%d\nx:\n", max_D);
    output_long_num(max_x);
    printf("y:\n");
    output_long_num(max_y);
       
/*    printf("last result: %lld^2-%d*%lld^2=1\n",max_x,max_D,max_y);*/

    return 0;
}

