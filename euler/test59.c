#include <stdio.h>
#include <math.h>
#include <string.h>

#include "misc.h"

#define MAX_NUM 10000

int nums[MAX_NUM]={0};
int cnt =0;

int main()
{
    FILE *stream; int ch; int n,i,j,k,m;
    char tmp[100],tmp1; int sum=0; bool fail;
    stream = fopen("./files/cipher1.txt","r");
    if(stream == NULL)
    {
        printf("file open error\n");
        return 0;
    }
    fseek(stream, 0, SEEK_SET);
    n = 0;

    tmp[0]='\0';
    do {
      ch = fgetc (stream);
      if (ch== 44 || ch== EOF)
      {
        tmp[n]='\0'; 
        E_PRINTF("%s - %d\n", tmp, sum);
        nums[cnt++] = sum;
        n=0;
        tmp[0]='\0';
        sum = 0;
      }
      else
      {
        tmp[n++] = (char)ch;
        sum = sum*10+ch - '0';
      }
 
    } while (ch != EOF);
    fclose(stream);
    
    E_PRINTF("Total cnt: %d\n", cnt);

    nums[cnt-1] = 73;
    for(n=0;n<cnt;n++)
    {
        printf("%d - %d\n", n, nums[n]);
    }
    for(i=0;i<26;i++)
        for(j=0;j<26;j++)
            for(k=0;k<26;k++)
            {
                fail = FALSE;
                m=0;
                for(n=0;n<40;n++)
                {
                    
                    if(n%3==0)
                        ch = (i+'a') ^ nums[n];
                    if(n%3==1)
                        ch = (j+'a') ^ nums[n];
                    if(n%3==2)
                        ch = (k+'a') ^ nums[n];
                    tmp[m++] = ch;
   
                    if(ch == '{' || ch == '}' || ch == '*' 
                    || ch == '<' || ch == '>' || ch == '_' 
                    || ch == '$' || ch == '#' || ch == '^' || ch == '&'
                    || ch == '*' || ch == '%' || ch == '~' || ch == '`'
                    || ch == '|' || ch == '=' || ch == '@' 
                    || ch == '/' || ch == '+')
                    {
                        fail = TRUE;
                        break;
                    }
                   
                }
              
                tmp[39] = '\0';
                if(!fail /*&&(tmp[0]==' ' || (tmp[0] >= 'A' && tmp[0] <='z'))*/)
                {
                    printf("%c%c%c:",(i+'a'),(j+'a'),(k+'a'));  
                    printf("%s\n", tmp);
                }
            }
    printf("%d %d %d %d\n",'a','z','A','Z');            
    sum = 0;
    for(n=0;n<cnt;n++)
    {
                  
        if(n%3==0)
           ch = ('g') ^ nums[n];
        if(n%3==1)
           ch = ('o') ^ nums[n];
        if(n%3==2)
           ch = ('d') ^ nums[n];
        printf("%c",ch);
        sum +=ch;
    }
    printf("\nTotal sum:%d\n", sum);
    return 1;
}



