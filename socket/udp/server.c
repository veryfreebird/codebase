#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netdb.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define BUFSIZE  65500
#define DEFAULT_PORT  5320


enum{CMD_NAME,DST_PORT};
int execute(char *command,char *buf,int bufmax);

int main(int argc,char *argv[])
{
    struct sockaddr_in server;//服务器地址
    struct sockaddr_in client;//客户端地址
    int len;//sockaddr_in 的长度
    int port;//端口地址
    int s;//套接字描述符
    int cn;//接收到的命令的字数
    int sn;//发送报文的字节数
    int rn;//接收报文的字节数
    char cmd1[BUFSIZE];//第一个语句的命令
    char cmd2[BUFSIZE];//第二个语句的命令
    char recv_buf[BUFSIZE];//接收缓冲区
    char send_buf[BUFSIZE];//发送缓冲区
    /* 实际参数的处理*/
    if(argc==2){

        if ((port=atoi(argv[DST_PORT]))==0)    {
            struct servent *se;//服务器信息
            if((se=getservbyname(argv[DST_PORT],"udp") )!=NULL)
                port=(int)ntohs((u_short)se->s_port);
            else
            {
                fprintf(stderr,"getservbyname error\n");
                exit(EXIT_FAILURE);
            }    
        }
    }
    else
        port =DEFAULT_PORT;

    /*使用udp协议打开一个套接字*/
    if((s=socket(AF_INET,SOCK_DGRAM,0))<0)
    {
        perror("socket");
        exit(EXIT_FAILURE);
    } 

    memset((char*)&server,0,sizeof(server));
    server.sin_family=AF_INET;
    server.sin_addr.s_addr=htonl(INADDR_ANY);
    //server.sin_addr.s_addr=215546489;
    server.sin_port=htons(port);
    printf("port%d:\n", port);
    if(bind(s,(struct sockaddr *)&server,sizeof(server))<0)
    {
        perror("bind");
        exit(EXIT_FAILURE);
    }
    /*服务器处理的主要子程序*/
    len=sizeof(client);
    printf("wainting for connection...\n");
    while((rn=recvfrom(s,recv_buf,BUFSIZE-1,0,(struct sockaddr*)&client,&len))>0)
    {
        recv_buf[rn]='\0';
        printf("receive %s\n",recv_buf);
        /*接收到的命令处理*/
        if((cn=sscanf(recv_buf,"%s%s",cmd1,cmd2))<=0)
        {
            sn=0;
        }
        else if(cn==2&&strcmp(cmd1,"show")==0)
        {  
            if(strcmp(cmd2,"route")==0)
#ifdef linux
                sn=execute("/bin/netstat -rn",send_buf,BUFSIZE);
#else
            sn=execute("/usr/bin/netstat -rn",send_buf,BUFSIZE);
#endif
            else if(strcmp(cmd2,"arp")==0)
#ifdef linux
                sn=execute("/sbin/arp -an",send_buf,BUFSIZE);
#else
            sn=execute("/usr/bin/arp -an",send_buf,BUFSIZE);
#endif
            else if(strcmp(cmd2,"tcp")==0)
#ifdef linux 
                sn=execute("/bin/netstat -tn",send_buf,BUFSIZE);
#else
            sn=execute("/usr/bin/netstat -tn",send_buf,BUFSIZE);
#endif
            else if(strcmp(cmd2,"nic")==0)
                sn=execute("/sbin/ifconfig -a",send_buf,BUFSIZE);
            else{
                sn=sprintf(send_buf,"parameter error %s\n","show [route|arp|tcp|nic]\n",cmd2);
                printf("%s",send_buf);
            }
        }
        else if(cn==1&&strcmp(cmd1,"help")==0)
        {
            sn=sprintf(send_buf,"%s%s%s%s%s%s","Command:\n","show route \n","show arp \n","show tcp \n","show nic \n","help\n");
            sn=sizeof(send_buf);
        }
        else 
            sn=sprintf(send_buf,"Command error%s",cmd1);
        if(sendto(s,send_buf,sn,0,(struct sockaddr *)&client,len)<0)
            break;
        printf("%s",send_buf);
    }
    close(s);
    return EXIT_SUCCESS;
}
int execute(char *command,char *buf,int bufmax)
{
    FILE *fp;
    int i;
    if((fp=popen(command,"r"))==NULL)
    {
        perror(command);
        exit(EXIT_FAILURE);
    }
    i=0;
    while((buf[i++]=fgetc(fp))!=EOF&&i<bufmax);
    pclose(fp);
    return i;
}
