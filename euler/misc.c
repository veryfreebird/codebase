#include <stdio.h>
#include <math.h>
#include <string.h>
#include <malloc.h>
#include <stdlib.h>

#include "misc.h"

bool find_num_in_sorted_list(long long n, long long *list, int length)
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

bool find_num_in_sorted_list_1(int n, int *list, int length)
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


void output_long_num(int *a)
{
    int i;
    E_PRINTF("%d:", a[0]);
    for(i=a[0];i>=1;i--)
    {
        printf("%d",a[i]);
    }
    printf("\n");
}

int temp[N][N]={0};

void format_long_num(int n, int *num)
{
    int i=0;
    memset(num, 0, N*sizeof(int));
    for(;;)
    {
        if(n == 0)
            break;
        else
        {
            i++;
            num[i]=n % 10;
            n = n /10;
        }
    }
    num[0] = i;
}
void format_long_long_num(long long n, int *num)
{
    int i=0;
    memset(num, 0, N*sizeof(int));
    for(;;)
    {
        if(n == 0)
            break;
        else
        {
            i++;
            num[i]=n % 10;
            n = n /10;
        }
    }
    num[0] = i;
}

int cal_long_num(int *nums)
{
    int i, sum = 0;
    for(i=nums[0];i>0;i--)
        sum = sum *10 + nums[i];
    return sum;        
}


int sum_long_num_digits(int *num)
{
    int i,sum=0;
    for(i=0;i<num[0];i++)
    {
        sum += num[i+1];
    }
    return sum;
}


bool is_palindromic_long_num(int *num)
{
    int i;
    bool matched = TRUE;
    for(i=0;i<num[0];i++)
    {
        if(num[i+1] != num[num[0]-i])
        {
            matched = FALSE;
        }
    }
    return matched;    
}

void reverse_long_num(int *num, int*out)
{
    int i;
    for(i=0;i<num[0];i++)
    {
        out[i+1] = num[num[0]-i];
    }
    for(i=num[0];i>=1;i--)
        if(out[i] !=0)
            break;
    out[0] = i;
}


void cut_long_num(int n, int *num)
{
    if(num[0] <= n)
        return;
    
    num[0] = n;
    memset(&num[n+1], 0, (N-n-1)*sizeof(int));
    return;
    
}
 
void mul_long_nums(int *in_a, int *in_b, int *out_c)
{
    int *t1, *t2, overflow =0, tmp;
    int i,j, m;
    memset(temp, 0, N*N*sizeof(int));
    memset(out_c,0,N*sizeof(int));
    if(in_a[0] > in_b[0]){t1 = in_a; t2 = in_b;}
    else {t1=in_b; t2=in_a;}

    for(i=1;i<=t2[0];i++)
    {
        overflow = 0;
        for(j=1;j<=t1[0];j++)
        {
            tmp = t1[j]*t2[i]+overflow;
            if(tmp >= 10) overflow = tmp /10;
            else overflow = 0;
            temp[i][j] = tmp % 10;
        }
        if(overflow>0) {temp[i][0]=t1[0]+1;temp[i][temp[i][0]]=overflow;}
        else {temp[i][0]=t1[0];}
        if(i > 1)
        {
            for(j=temp[i][0]+i-1;j>i-1;j--)
                temp[i][j] = temp[i][j-i+1];
            for(j=i-1;j>0;j--)
                temp[i][j] = 0;
            temp[i][0] =temp[i][0]+i-1;
        }
    }

    for(i=2;i<=t2[0];i++)
    {
        overflow = 0;
        m = (temp[1][0] > temp[i][0])? temp[1][0]: temp[i][0];
        for(j=1;j<=m;j++)
        {
            tmp = temp[1][j]+temp[i][j]+overflow;
            if(tmp>=10) overflow = tmp/10;
            else overflow =0;
            temp[1][j] = tmp %10;
        }
        if(overflow>0) {temp[1][0]=m+1;temp[1][temp[1][0]]=overflow;}
        else {temp[1][0]=m;}        
    }

    memcpy(out_c, temp[1], N*sizeof(int));
    
}

void sum_long_nums(int *in_a, int *in_b, int *out_c)
{
    int *t1, *t2, overflow =0, tmp;
    int i,j, m;
    memset(out_c, 0, N*sizeof(int));
    
    if(in_a[0] > in_b[0]){t1 = in_a; t2 = in_b;}
    else {t1=in_b; t2=in_a;}

    for(i=1;i<=t1[0];i++)
    {
        if(i<=t2[0])
            tmp = t1[i]+t2[i]+overflow;
        else
            tmp = t1[i]+overflow;
        if(tmp >= 10) overflow = tmp /10;
        else overflow = 0;
        out_c[i] = tmp % 10;
    }
    if(overflow>0) {out_c[0]=t1[0]+1;out_c[out_c[0]]=overflow;}
    else {out_c[0]=t1[0];}       
    
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

int compare_long_nums(int *in_a, int *in_b)
{
    int m;
    if(in_a[0] > in_b[0])
        return 1;
    if(in_a[0] < in_b[0])
        return -1;
    for(m=in_a[0];m>0;m--)
    {
        if(in_a[m] > in_b[m])
            return 1;
        if(in_a[m] < in_b[m])
            return -1;        
    }
    return 0;
}

void mul_value(char *in, char *out, int mul_num, int len)
{
  int i, tmp, overflow=0;
  for(i=0;i<len;i++)
  {
    tmp = in[i]*mul_num + overflow;
    out[i] = tmp % 10;
    if(tmp >= 10) overflow = tmp/10;
    else overflow = 0;
    
    E_PRINTF("%d ", out[i]);
  }
}

int check_seq_length(long long num)
{
  int length=0;
  for(;;)
  {
    length++;
    if(num == 1)
    {
      E_PRINTF("%lld total:%d\n",num,length);
      break;    
    }
    else
      E_PRINTF("%lld->",num);    
    if(num%2 ==0) num=num/2;
    else num=3*num+1; 
  }
  return length;
}

int check_factor_cnt(long long num)
{

    long long i,cnt=0;
    E_PRINTF("%lld: ",num);
    
    for(i=1;i<num/2+1; i++)
    {
        if(num % i ==0)
        {
            cnt++;
            E_PRINTF("%4lld ", i);
        }
    }
    E_PRINTF("%4lld =%lld=\n",num, cnt+1);
    return cnt+1;
}

long long check_factor_sum(long long num)
{

    long long i,cnt=0, sum=0;
    E_PRINTF("%lld: ",num);
    
    for(i=1;i<num/2+1; i++)
    {
        if(num % i ==0)
        {
            cnt++;
            sum += i;
            E_PRINTF("%4lld ", i);
        }
    }
    E_PRINTF("%4lld =%lld=%lld\n",num, cnt+1,sum);
    return sum;
}


void sum_100_dec(int *num1, int *num2, int *sum)
{
   int one_sum, overflow=0, i;
   for(i=99;i>=0;i--)
   {
    one_sum = num1[i] + num2[i] + overflow;
    sum[i] = one_sum % 10;
    if(one_sum >= 10) overflow = 1;
    else overflow =0;
   }
   
}

int *prime_samples = NULL;
int prime_length = 0; 
int prime_check_num = 0;
int max_num_to_check = 0;

bool is_prime(int num)
{
    int i, temp;

    if(num == 1)
        return FALSE;
    if(num == 2 || num ==5)
        return TRUE;
     temp = num % 10;
     if(temp == 1 || temp == 3 || temp == 7 || temp == 9)
     {
         for(i=2;i<(int)sqrt(num)+2;i++)
         {
             if(num % i == 0)
                 return FALSE;
         }
         return TRUE;
    }
    else
        return FALSE;
}

bool constrcut_prime_check(int max_num)
{
    int i;
    prime_check_num = sqrt(max_num)+1;
    max_num_to_check = max_num;
    prime_samples = malloc(prime_check_num*sizeof(int));
    if(prime_samples == NULL)
        return FALSE;
    for(i=1;i<prime_check_num;i++)
    {
        if(is_prime(i))
        {
            prime_samples[prime_length++]=i;
        }
    }
    return TRUE;
        
}



/*make sure num > prime_samples*/       
bool is_prime_fast(int num, int *prime_samples, int sample_length, int max_sample)
{

    int i;
    if(prime_samples == NULL)
    {
        printf("Wrong sample pointer\n");
        exit(-1);
    }
            
    if(num <= max_sample)
        printf("Error input as num %d <= max sample %d", num, max_sample);
    for(i=0; i< sample_length; i++)
    {
        if(num % prime_samples[i] == 0)
            return FALSE;
    }
    return TRUE;
}    

bool check_prime_with_samples(int num)
{

    if(num <= prime_check_num)
        return is_prime(num);
    else
        return is_prime_fast(num, prime_samples, prime_length, prime_samples[prime_length-1]);
 
} 

bool deconstruct_prime_check()
{
    if(prime_samples != NULL) free(prime_samples);
    prime_samples = NULL;
    prime_length = 0; 
    prime_check_num = 0;
    max_num_to_check = 0;

    return TRUE;
        
}

long long *prime_samples_long = NULL;
long long prime_length_long = 0; 
long long prime_check_num_long = 0;
long long max_num_to_check_long = 0;


bool constrcut_prime_check_long(long long max_num)
{
    long long i;
    prime_check_num_long = sqrt(max_num)+1;
    max_num_to_check_long = max_num;
    prime_samples_long = malloc(prime_check_num_long*sizeof(long long));
    if(prime_samples_long == NULL)
        return FALSE;
    for(i=1;i<prime_check_num_long;i++)
    {
        if(is_prime((int)i))
        {
            prime_samples_long[prime_length_long++]=i;
        }
    }
    return TRUE;
        
}
bool deconstruct_prime_check_long ()
{
    if(prime_samples_long  != NULL) free(prime_samples_long );
    prime_samples_long  = NULL;
    prime_length_long  = 0; 
    prime_check_num_long  = 0;
    max_num_to_check_long  = 0;

    return TRUE;
        
}
/*make sure num > prime_samples*/       
bool is_prime_fast_long(long long num, long long *prime_samples, long long sample_length, long long max_sample)
{

    long long i;
    if(prime_samples_long == NULL)
    {
        printf("Wrong sample pointer\n");
        exit(-1);
    }
            
    if(num <= max_sample)
        printf("Error input as num %lld <= max sample %lld", num, max_sample);
    for(i=0; i< sample_length; i++)
    {
        if(num % prime_samples[i] == 0)
            return FALSE;
    }
    return TRUE;
}    

bool check_prime_with_samples_long(long long num)
{

    if(num <= prime_check_num_long)
        return is_prime((int)num);
    else
        return is_prime_fast_long(num, prime_samples_long, prime_length_long, prime_samples_long[prime_length_long-1]);
 
} 


int sum_prime_samples(int *prime_samples, int sample_length)
{

    int i,sum =0;
    for(i=0; i< sample_length; i++)
    {
        sum += prime_samples[i];
    }
    return sum;
} 

bool is_palindromic_num(int num, int base)
{
    int temp = num, new_num = 0;
    for(;;)
    {
        if(temp ==0)
            break;

        new_num = new_num*base + (temp % base);
        temp = temp /base;
    }
    if(num == new_num)
        return TRUE;
    else
        return FALSE;
}

int check_length(int num)
{
    int i=0; int tmp=num;
    for(;;)
    {
        if(tmp == 0)
            break;
        tmp = tmp /10;
        i++;            
    }
    return i;
    
}

int next_circular_num(int num, int len)
{
    int base = pow(10,len-1);
  
    return (num/base+ (num % base)*10);
}

int truncat_num_from_left(int num, int length)
{
    int base = pow(10, length-1);
    return (num % base);
}

int truncat_num_from_right(int num)
{
    return (num/10);
}
int cat_int_num(int num1, int num2)
{
    return num1*(pow(10, check_length(num2)))+num2;

}
bool is_n_pandigital_num(int nn, int num)
{
    char mark[9] = {0}; int n,j;
    if(check_length(num) != nn) return FALSE;
    
    j = num;
    for(;;)
    {
        if(j==0)break;
        else
        {
            n = j %10;
            if(n == 0 || n > nn || mark[n-1] == 1)
                return FALSE;
            else
               mark[n-1] = 1;
            j = j / 10;
            
        }
    }
    return TRUE;
    
}
int check_long_length(long long num)
{
    int i=0; long long tmp=num;
    for(;;)
    {
        if(tmp == 0)
            break;
        tmp = tmp /10;
        i++;            
    }
    return i;

}

bool is_n_pandigital_num_1(int nn, long long num)
{
    char mark[10] = {0}; int n; long long j;
#if 0    
    if(check_long_length(num) != nn) 
    {
        E_PRINTF("lenth: checked:%d - input: %d\n", check_long_length(num), nn);
        return FALSE;
    }
#endif    
    j = num;
    for(;;)
    {
        if(j==0)break;
        else
        {
            n = j %10;
            if(n >= nn || mark[n] == 1)
                return FALSE;
            else
               mark[n] = 1;
            j = j / 10;
            
        }
    }
    return TRUE;
    
}

/**
 *  m[0] m[1] m[2] m[3] m[4]
 *  1    3    2    5    4
 **/  

bool find_next_perm(int n, char *m, char *num)
{
    int i, k; char tmp; int l;
    bool found = FALSE;
    for(i=n-1;i>0;i--)
        if(m[i-1] < m[i])
        {
            found = TRUE;
            k = i-1;
            break;    
        }
    if(!found)
        return FALSE;
    
    tmp = n;    
    for(i=k+1;i<=n-1;i++)
        if(m[i] > m[k] && m[i] - m[k] < tmp)
        {
            l = i;
            tmp = m[i] - m[k];
        }
    
    /*swap k and l*/
    tmp = m[k];
    m[k] = m[l];
    m[l] = tmp;
    
    memcpy(num, m, n);
    /*sort from k+1 to n-1*/
    for(i=k+1;i<=n-2;i++)
        for(l=i+1;l<=n-1;l++)
            if(num[i] > num[l])
            {
                tmp = num[i];
                num[i] = num[l];
                num[l] = tmp;
            }
    for(i=0;i<n;i++)
        E_PRINTF("%d ", num[i]);
    E_PRINTF("\n");
    return TRUE;
}

unsigned long long cal_perm_num(int n, char *nums)
{
    unsigned long long sum = 0;
    int i;
    for(i=0;i<n;i++)
        sum = sum *10 + nums[i];
    return sum;        
}

int cal_pentagonal_num(int n)
{
    int m = n*(3*n-1)/2;
    return m;
}
bool is_pentagonal_num(long long num)
{
    long long m;
    m = sqrt(1+24*num);

    if(m>=5 && ((m+1) % 6 == 0) && (m*m == (1+24*num)))
        return TRUE;
    else
        return FALSE;
}

long long cal_triangle_num(long long n)
{
    long long m = n*(n+1)/2;
    return m;
}

bool is_hexagonal_num(long long num)
{
    long long m;
    m = sqrt(1+8*num);

    if(m>=3 && ((m+1) % 4 == 0) && (m*m == (1+8*num)))
        return TRUE;
    else
        return FALSE;
}
