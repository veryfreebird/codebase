#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <netdb.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define BUFSIZE 65500
#define DEFAULT_PORT 5320

enum{CMD_NAME,DST_IP,DST_PORT};

int main(int argc,char *argv[])
{
    struct sockaddr_in server;//服务器地址
    struct sockaddr_in client;//客户端地址
    unsigned long dst_ip;//服务器IP地址
    int port ;//端口号
    int s;//套接自描述
    int n;//输入数据的字节数
    char buf[BUFSIZE];//接收缓冲去
    char cmd[BUFSIZE];//发送缓冲区
    int zero;
    /*实际参数检查*/
    if(argc!=2&&argc!=3)
    {
        fprintf(stderr,"Usage:%s hostname [port]",argv[0]);
        exit(EXIT_FAILURE);
    }
    if((dst_ip=inet_addr(argv[DST_IP]))==INADDR_NONE)
    { struct hostent *he;

        if((he=gethostbyname(argv[DST_IP]))==NULL)
        {
            fprintf(stderr,"gethostbyname error\n");
            exit(EXIT_FAILURE);
        }
        memcpy((char *)&dst_ip,(char *)he->h_addr,he->h_length);
    }

    if(argc==3)
    {
        if((port=atoi(argv[DST_PORT]))==0)
        {
            struct servent *se;
            if((se=getservbyname(argv[DST_PORT],"udp"))!=NULL)
            {
                port=(int)ntohs((u_short)se->s_port);
            }
            else
            { 
                fprintf(stderr,"getservbyname error");
                exit(EXIT_FAILURE);
            }
        }
    }
    else 
        port=DEFAULT_PORT;
    if((s=socket(AF_INET,SOCK_DGRAM,0))<0)
    {
        perror("socket");
        exit(EXIT_FAILURE);
    }
    memset((char *)&client ,0,sizeof(client));
    client.sin_family=AF_INET;
    client.sin_addr.s_addr=htonl(INADDR_ANY);
    client.sin_port=htons(0);
    if(bind(s,(struct sockaddr *)&client,sizeof(client))<0)
    {
        perror("bind");
        exit(EXIT_FAILURE);
    }
    memset((char *)&server,0,sizeof(server));
    server.sin_family=AF_INET;
    server.sin_addr.s_addr=dst_ip;
    inet_pton(AF_INET, argv[DST_IP], &server.sin_addr); 
    server.sin_port=htons(port);
    zero=0;
    printf("UDP>");
    fflush(stdout);
    //printf("outof while\n");
    //printf("%ld",dst_ip);

    while((n=read(0,buf,BUFSIZE))>0)
    {
        buf[n]='\0';
        sscanf(buf,"%s",cmd);

        if(strcmp(cmd,"quit")==0)
        {
            break;
        }
        if(sendto(s,buf,n,0,(struct sockaddr*)&server,sizeof(server))<0)
        {
            break;
        }

        if((n=recvfrom(s,buf,BUFSIZE-1,0,(struct sockaddr*)0,&zero))<0)
            break;
        buf[n]='\0';
        printf("%s",buf);
        printf("UDP>");
        fflush(stdout);
    }
    close(s);
    return EXIT_SUCCESS;
}
