#include <stdio.h>

short data0[]={0,0x1234,0xFFFF,0,0,0x0000};
short data1[]={0,0x1234,0xFFFF,0,0,0xFFFF};
unsigned short checksum (unsigned short *buffer,int size)
{
    unsigned long cksum=0;
    while (size>1)
    {
        cksum +=*buffer++;
        size -=sizeof(unsigned short);
    }
    if (size)
    {
        cksum +=*(unsigned char *) buffer;
    }
    while (cksum>>16)
        cksum = (cksum>>16) + (cksum & 0xffff);
    return (unsigned short) (~cksum);
}



int main()
{
    int size = sizeof(data0);
    data0[0] = checksum(data0, size);
    printf("data0 checksum = %x\n", data0[0]);
    printf("data0 validation = %x\n", checksum(data0, size));
    data1[0] = checksum(data1, size);
    printf("data1 checksum = %x\n", data1[0]);
    printf("data1 validation = %x\n", checksum(data1, size));
    return 0;
}
