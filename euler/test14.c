#include <stdio.h>
#include <math.h>
#include <string.h>
#include "misc.h"

#define MAX_NUM 1000000LL
int main()
{
  long long i,save; int len=0,tmp_len=0;
  for(i=1;i<MAX_NUM;i++)
  {
    tmp_len = check_seq_length(i);
    if(tmp_len>len) {len=tmp_len; save=i;}
  }    
  printf("\nresult: %lld, len: %d\n", save, len);
    
	return 1;
	
    
}
