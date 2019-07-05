#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

struct sockaddr_in localSock;
struct ip_mreq group;
struct sockaddr serveraddr;
int serveraddr_len=200;
int sd;
int datalen;
char databuf[1500];

int main(int argc, char *argv[])
{
    int loop = 1, cnt, r;
    int err = -1;
    sd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sd < 0)
    {
        perror("Opening datagram socket error");
        exit(1);
    }
    else
        printf("Opening datagram socket....OK.\n");

    {
        int reuse = 1;
        if (setsockopt(sd, SOL_SOCKET, SO_REUSEADDR, (char *)&reuse, sizeof(reuse)) < 0)
        {
            perror("Setting SO_REUSEADDR error");
            close(sd);
            exit(1);
        }
        else
            printf("Setting SO_REUSEADDR...OK.\n");
    }

    memset((char *)&localSock, 0, sizeof(localSock));
    localSock.sin_family = AF_INET;
    localSock.sin_port = htons(4321);
    localSock.sin_addr.s_addr = htonl(INADDR_ANY);
    if (bind(sd, (struct sockaddr *)&localSock, sizeof(localSock)))
    {
        perror("Binding datagram socket error");
        close(sd);
        exit(1);
    }
    else
        printf("Binding datagram socket...OK.\n");

    /*设置回环许可*/
    err = setsockopt(sd, IPPROTO_IP, IP_MULTICAST_LOOP, &loop, sizeof(loop));
    if (err < 0)
    {
        perror("setsockopt():IP_MULTICAST_LOOP");
        return -3;
    }

    group.imr_multiaddr.s_addr = inet_addr("226.1.1.1");
    group.imr_interface.s_addr = inet_addr("10.0.2.15");
    if (setsockopt(sd, IPPROTO_IP, IP_ADD_MEMBERSHIP, (char *)&group, sizeof(group)) < 0)
    {
        perror("Adding multicast group error");
        close(sd);
        exit(1);
    }
    else
        printf("Adding multicast group...OK.\n");

    for (cnt = 0; cnt < 10; cnt++)
    {
        datalen = sizeof(databuf);
        if ((r = recvfrom(sd, databuf, datalen, 0, &serveraddr, &serveraddr_len)) < 0)
        {
            perror("Reading datagram message error");
            close(sd);
            exit(1);
        }
        else
        {
            printf("Reading datagram message...OK.\n");
            printf("The message from multicast server is: %s\n", databuf);
        }
    }
    close(sd);
    return 0;
}
