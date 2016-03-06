#include <stdio.h>
#include <math.h>
#include <string.h>

#include "misc.h"

#define MAX_NAME_NUM 10000
char names[MAX_NAME_NUM][20] = {0};

int cnt = 0;
void insert(char *name)
{
    int i, j;
    for(i=0;i<cnt;i++)
    {
        if(strcmp(names[i], name)>0)
        {
            for(j = MAX_NAME_NUM-1; j > i; j--)
            {
                strcpy(names[j], names[j-1]);
            }
            strcpy(names[i], name);
            cnt++;
            return;
        }
    }
    strcpy(names[cnt++], name);
}


long long cal_value(char *name, int n)
{
    int i,j; long long sum=0;
    i = strlen(name);
    for(j=0; j<i; j++)
    {
        sum += name[j]-'A'+1;
    }
    return sum*n;
}

int main()
{
    FILE *stream; int ch; int n;
    char tmp[20],tmp1; long long sum=0;
    stream = fopen("./files/names.txt","r");
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
        insert(tmp);        
        n=0;
        tmp[0]='\0';
      }
      else if (ch != 34)
      {
        tmp[n++] = (char)ch;
      }
 
    } while (ch != EOF);

    for(n=0; n<cnt;n++)
    {
        sum +=cal_value(names[n],n+1);
    }

    printf("Total sum: %lld\n", sum);

    fclose(stream);
    return 1;
}
