#include <stdio.h>
#include <math.h>
#include <string.h>
#include "misc.h"


#define MAX_SAMPLE_LENGTH  20000
int factor_cnt[MAX_SAMPLE_LENGTH+2]={0};

#define MAX_NUM 500

int main()
{
	long long i=0, m, n;
	for(i=0;i<MAX_SAMPLE_LENGTH+2;i++)
	{
		factor_cnt[i]=check_factor_cnt(i+1);
		/*printf("%d ", factor_cnt[i]);*/
	}
	for(i=1;i<MAX_SAMPLE_LENGTH/2;i++)
	{
		if(factor_cnt[2*i-1-1]*factor_cnt[i-1] >=MAX_NUM)
		{
			printf("find %lld, %lld", (2*i-1)*i, 2*i-1);
			break;
		}
		if(factor_cnt[i-1]*factor_cnt[2*i] >=MAX_NUM)
		{
			printf("find %lld, %lld",i*(2*i+1), 2*i);
			break;
		}
	}
	
	return 1;
	
    
}
