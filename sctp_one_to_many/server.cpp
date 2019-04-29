#include "server.h"
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <stdio.h>
#include <arpa/inet.h>

SctpServer::SctpServer()
    :streamIncrement_(1)
{

}

void SctpServer::listenSocket(void)
{
    //创建SCTP套接字
    sockFd_ = socket(AF_INET,SOCK_SEQPACKET,IPPROTO_SCTP);
    bzero(&serverAddr_,sizeof(serverAddr_));
    serverAddr_.sin_family = AF_INET;
    serverAddr_.sin_addr.s_addr = htonl(INADDR_ANY);
    serverAddr_.sin_port = htons(SERVER_PORT);
    inet_pton(AF_INET,"127.0.0.1",&serverAddr_.sin_addr);   

    //地址绑定
    bind(sockFd_,(struct sockaddr *)&serverAddr_,sizeof(serverAddr_));

    //设置SCTP通知事件(此处只设置了I/O通知事件)
    bzero(&events_,sizeof(events_));
    events_.sctp_data_io_event = 1;
    setsockopt(sockFd_,IPPROTO_SCTP,SCTP_EVENTS,&events_,sizeof(events_));

    //开始监听
    listen(sockFd_,LISTEN_QUEUE);
}

void SctpServer::loop(void)
{
    while(true)
    {
        len_ = sizeof(struct sockaddr_in);
        //从socket读取内容
        readSize_ = sctp_recvmsg(sockFd_,readBuf_,BUFFER_SIZE,
                                 (struct sockaddr *)&clientAddr_,&len_,&sri_,&messageFlags_);
        //增长消息流号
        if(streamIncrement_)
        {
            sri_.sinfo_stream++;
        }
        sctp_sendmsg(sockFd_,readBuf_,readSize_,
                     (struct sockaddr *)&clientAddr_,len_,
                      sri_.sinfo_ppid,sri_.sinfo_flags,sri_.sinfo_stream,0,0);
    }
}

void SctpServer::start(void)
{
    listenSocket();
    loop();
}

