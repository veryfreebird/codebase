#include <stdio.h>

int main()
{
    unsigned int hash,b;
    for(hash=0;hash<=(unsigned int)(-1);hash++)
    {
        int b = ((hash >>8)*2)>>24;
        if (b==1){printf("%u:%d ",hash,b);break;}
    }
}
