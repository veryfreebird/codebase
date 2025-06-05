#include<stdio.h>

void FindMax(int a[])
{
	int i,mi=0,ma=0;
	int min=a[0],max=a[0];
	for (i=0;i<10;i++)
	{
		if (a[i]<min)
		{
			min=a[i];
			mi=i;
		}
		if (a[i]>max)
		{
			max=a[i];
			ma=i;
		}
	}
	int tmp=a[mi];
	a[mi]=a[ma];
	a[ma]=tmp;

 } 
 int main()
 {
 	int a[10];
 	int i;
 	for (i=0;i<10;i++)
 	{
 		scanf("%d",&a[i]);
	 }

	FindMax(a);
	for (i=0;i<10;i++)
 	{
 		printf("%d ",a[i]);
    }
	printf("\n");
	fflush(stdout);

	FindMax(a);
	for (i=0;i<10;i++)
 	{
 		printf("%d ",a[i]);
    }
    return 0;
 }
