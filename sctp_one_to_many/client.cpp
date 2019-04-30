#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/sctp.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#define SERVER_PORT 6666 
#define MAXLINE     1024

/×Ways to check ongoing SCTP links
cat /proc/net/sctp/eps
cat /proc/net/sctp/assocs
×/


void sctpstr_cli(FILE *fp,int sock_fd,struct sockaddr *to,socklen_t tolen);

class SctpClient
{
    public:
        SctpClient():echoToAll_(0)
        {

        }
        ~SctpClient()
        {
            close(sockFd_);
        }
        //��ͻ���
        void start(void)
        {
            makeSocket();
        }

    private:

        void makeSocket(void)
        {
            sockFd_ = socket(AF_INET,SOCK_SEQPACKET,IPPROTO_SCTP);
            bzero(&clientAddr_,sizeof(clientAddr_));
            clientAddr_.sin_family = AF_INET;
            clientAddr_.sin_addr.s_addr = htonl(INADDR_ANY);
            clientAddr_.sin_port = htons(9999);
            inet_pton(AF_INET,"127.0.0.1",&clientAddr_.sin_addr);       
            bind(sockFd_,(struct sockaddr *)&clientAddr_,sizeof(clientAddr_));        
                
            bzero(&serverAddr_,sizeof(serverAddr_));
            serverAddr_.sin_family = AF_INET;
            serverAddr_.sin_addr.s_addr = htonl(INADDR_ANY);
            serverAddr_.sin_port = htons(SERVER_PORT);
            inet_pton(AF_INET,"127.0.0.1",&serverAddr_.sin_addr);

            bzero(&events_,sizeof(events_));
            events_.sctp_data_io_event = 1;
            setsockopt(sockFd_,IPPROTO_SCTP,SCTP_EVENTS,&events_,sizeof(events_));
            if(echoToAll_ == 0)
            {
                sctpstr_cli(stdin,sockFd_,(struct sockaddr *)&serverAddr_,sizeof(serverAddr_));
            }
        }

        int sockFd_;
        struct sockaddr_in serverAddr_, clientAddr_;
        struct sctp_event_subscribe events_;
        int echoToAll_;
};

//ѭ�����Ͳ�������Ϣ
void sctpstr_cli(FILE *fp,int sock_fd,struct sockaddr *to,socklen_t tolen)
{
    struct sockaddr_in peeraddr;
    struct sctp_sndrcvinfo sri;
    char sendline[MAXLINE];
    char recvline[MAXLINE];
    socklen_t len;
    int out_sz,rd_sz;
    int msg_flags;

    bzero(&sri,sizeof(sri));
    while(fgets(sendline,MAXLINE,fp) != NULL)
    {
        if(sendline[0] != '[')
        {
            printf("ERROR\n");
            continue;
        }
        sri.sinfo_stream = sendline[1] - '0';
        out_sz = strlen(sendline);

        //������Ϣ
        int count = sctp_sendmsg(sock_fd,sendline,out_sz,to,tolen,0,0,sri.sinfo_stream,0,0);
        len = sizeof(peeraddr);
        
        bzero(recvline, MAXLINE);
        rd_sz = sctp_recvmsg(sock_fd,recvline, MAXLINE,
                             (struct sockaddr *)&peeraddr,&len,&sri,&msg_flags);
        if(rd_sz != -1)
        {
            printf("From str:%d seq:%d (assoc:%d):",
                sri.sinfo_stream,sri.sinfo_ssn,(u_int)sri.sinfo_assoc_id);
            printf("%d  %s\n",rd_sz,recvline);
        }
        else
        {
            perror("RECV ERROR:");
        }
    }
}

int main(int argc,char **argv)
{
  SctpClient client;
  client.start();
  return 0;
}
