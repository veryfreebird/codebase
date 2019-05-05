#pragma once

#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/sctp.h>

#define SERVER_PORT 6666
#define SERVER2_PORT 7777

#define BUFFER_SIZE 1024
#define LISTEN_QUEUE 100

class SctpServer
{
    public:
        SctpServer();
        void start(void);
    private:
        //��������socket
        void listenSocket(void);
        //ѭ����������
        void loop(void);

        int sockFd_;                            //�������ܵ��׽���
        int messageFlags_;                      //��Ϣ����
        char readBuf_[BUFFER_SIZE];             //���ܻ�����
        struct sockaddr_in clientAddr_;         //��������ͻ��˵�ַ
        struct sockaddr_in serverAddr_;         //�����������˵�ַ
        struct sctp_sndrcvinfo sri_;            //��Ϣ���ϸ����Ϣ
        struct sctp_event_subscribe events_;    //�¼���
        int streamIncrement_;                   //����
        socklen_t len_;                         //��ַ����
        size_t readSize_;                       //�����Ĵ�С
};

