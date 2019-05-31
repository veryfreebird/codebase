/* File Name: server.c */  
#include<stdio.h>  
#include<stdlib.h>  
#include<string.h>  
#include<errno.h>  
#include<sys/types.h>  
#include<sys/socket.h>  
#include<netinet/in.h>  
#include<unistd.h>
#define DEFAULT_PORT 8000  
#define MAXLINE 4096  
int main(int argc, char** argv)  
{  
    int    socket_fd, connect_fd;  
    struct sockaddr_in     servaddr;  
    char    buff[4096];  
    int     n;  
    pid_t   pid;
    //初始化Socket  
        if( (socket_fd = socket(AF_INET, SOCK_STREAM, 0)) == -1 ){  
            printf("create socket error: %s(errno: %d)\n",strerror(errno),errno);  
            exit(0);  
        }  
    //初始化  
    memset(&servaddr, 0, sizeof(servaddr));  
    servaddr.sin_family = AF_INET;  
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);//IP地址设置成INADDR_ANY,让系统自动获取本机的IP地址。  
    servaddr.sin_port = htons(DEFAULT_PORT);//设置的端口为DEFAULT_PORT  

    //将本地地址绑定到所创建的套接字上  
    if( bind(socket_fd, (struct sockaddr*)&servaddr, sizeof(servaddr)) == -1){  
        printf("bind socket error: %s(errno: %d)\n",strerror(errno),errno);  
        exit(0);  
    }  
    if( listen(socket_fd, 10) == -1){  
        printf("listen socket error: %s(errno: %d)\n",strerror(errno),errno);  
        exit(0);  
    }  
    printf("======waiting for client's request======\n");  
    while(1)
    {  
        //阻塞直到有客户端连接，不然多浪费CPU资源。  
        if( (connect_fd = accept(socket_fd, (struct sockaddr*)NULL, NULL)) == -1){  
            printf("accept socket error: %s(errno: %d)",strerror(errno),errno);  
            continue;  
        }  
        //向客户端发送回应数据  
        if((pid = fork()) == 0)
        {
            if(send(connect_fd, "Hello,you are connected!\n", 26,0) == -1)  
                perror("send error");  
            while(1)
            {
                 n = recv(connect_fd, buff, MAXLINE, 0); 
                 buff[n]= '\0';
                 send(connect_fd,buff, 26, 0); 
                 if(strncmp(buff,"quit", 4)==0)
                    break;                 
            }
            printf("process %d quit!\n", getpid()); 
            close(connect_fd); 
            sleep(1);
            exit(0);  
        }
        else
        {
            printf("process %d forked!\n", pid);
        }
          
    }  
    close(socket_fd);  
    exit(0);
}  
