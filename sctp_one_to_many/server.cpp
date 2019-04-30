#include "server.h"
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <stdio.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/sctp.h>
#include <stdlib.h>


static void handle_event(void *buf)
{

	struct sctp_assoc_change   *sac;
	struct sctp_send_failed    *ssf;
	struct sctp_paddr_change   *spc;
	struct sctp_remote_error   *sre;
	struct sctp_shutdown_event *sse;

	union sctp_notification  *snp;

	snp = (sctp_notification*)buf;
	switch (snp->sn_header.sn_type)
	{

		case SCTP_ASSOC_CHANGE:
		{
			sac = &snp->sn_assoc_change;
			printf("assoc_change: state=%hu, error=%hu, instr=%hu outstr=%hu associd=%d\n", 
				sac->sac_state, 
				sac->sac_error,
				sac->sac_inbound_streams, 
				sac->sac_outbound_streams,
				sac->sac_assoc_id);
			break;
		}
		case SCTP_SEND_FAILED:
		{
			ssf = &snp->sn_send_failed;
			printf("sendfailed: len=%hu err=%d assoc_i=%d ssf_data=%d\n", ssf->ssf_length, ssf->ssf_error, ssf->ssf_assoc_id, ssf->ssf_data[0]);
			break;
		}
		case SCTP_PEER_ADDR_CHANGE:
		{
			spc = &snp->sn_paddr_change;
			struct sockaddr_in  *sin = (struct sockaddr_in *)&spc->spc_aaddr;
			char  addrbuf[INET6_ADDRSTRLEN];
			inet_ntop(AF_INET, &sin->sin_addr, addrbuf, INET6_ADDRSTRLEN);
			printf("peeraddrchange: %s state=%d, error=%d\n", addrbuf, spc->spc_state, spc->spc_error);
			break;
		}
		case SCTP_REMOTE_ERROR:
		{
			sre = &snp->sn_remote_error;
			printf("remote_error: err=%hu len=%hu\n", ntohs(sre->sre_error), ntohs(sre->sre_length));
			break;
		}

		case SCTP_SHUTDOWN_EVENT:
		{
			sse = &snp->sn_shutdown_event;
			printf("shutdown event: assoc_id=%d\n", sse->sse_assoc_id);
			break;
		}
		default:
		{
			printf("unknown type: %hu\n", snp->sn_header.sn_type);
			break;
		}
	}
}

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

    //设置SCTP通知事件
    bzero(&events_,sizeof(events_));
    events_.sctp_data_io_event = 1;
	events_.sctp_association_event = 1;
	events_.sctp_address_event = 1;
	events_.sctp_send_failure_event = 1;
	events_.sctp_peer_error_event = 1;
	events_.sctp_shutdown_event = 1;
	events_.sctp_partial_delivery_event = 1;
    events_.sctp_adaption_layer_event = 1;

    setsockopt(sockFd_,IPPROTO_SCTP,SCTP_EVENTS,&events_,sizeof(events_));

    //开始监听
    listen(sockFd_,LISTEN_QUEUE);
}

void SctpServer::loop(void)
{
    char addrbuf[100];
    while(true)
    {
        len_ = sizeof(struct sockaddr_in);
        //从socket读取内容
        bzero(&clientAddr_,sizeof(clientAddr_));
        readSize_ = sctp_recvmsg(sockFd_,readBuf_,BUFFER_SIZE,
                                 (struct sockaddr *)&clientAddr_,&len_,&sri_,&messageFlags_);

        if (messageFlags_ &  MSG_NOTIFICATION)
        {
        	printf("****************************************************\n");
        	printf("Event: notificaiton length=%d\n", readSize_);
        	handle_event((void*)readBuf_);
        }
        else
        {
        	printf("****************************************************\n");
        	printf("Event: data event length=%d\n", readSize_);
        	inet_ntop(AF_INET, &clientAddr_.sin_addr, addrbuf, INET_ADDRSTRLEN);
        	int port = ntohs(clientAddr_.sin_port);
        	printf("data from=%s:%d\n", addrbuf, port);
        	printf("data=%s\n", readBuf_);
        
            //增长消息流号
            if(streamIncrement_)
            {
                sri_.sinfo_stream++;
            }
            sctp_sendmsg(sockFd_,readBuf_,readSize_,
                         (struct sockaddr *)&clientAddr_,len_,
                          sri_.sinfo_ppid,sri_.sinfo_flags,sri_.sinfo_stream,0,0);
	        /*forward to another server*/
            bzero(&clientAddr_,sizeof(clientAddr_));
            clientAddr_.sin_family = AF_INET;
            clientAddr_.sin_addr.s_addr = htonl(INADDR_ANY);
            clientAddr_.sin_port = htons(SERVER2_PORT);
            inet_pton(AF_INET,"127.0.0.1",&clientAddr_.sin_addr); 				
            sctp_sendmsg(sockFd_,readBuf_,readSize_,
                         (struct sockaddr *)&clientAddr_,len_,
                          sri_.sinfo_ppid,sri_.sinfo_flags,sri_.sinfo_stream,0,0);
        }                 
    }
}

void SctpServer::start(void)
{
    listenSocket();
    loop();
}

