#include <stdio.h>
#include <stdlib.h>
#include <net/if.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <arpa/inet.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <net/route.h>
#include <string.h>
#include <net/if_arp.h>

int main()
{
    struct sockaddr_in *sin;
    struct ifreq ifr;
    FILE *dns;
    FILE *gw;
    char *ip = new char(16);
    char *netmask = new char(16);
    char *broadcast = new char(16);
    //char *ip = (char *)malloc(16);
    char *mac = new  char(32);
    //char *mac = (char *)malloc(32);
    int mtu;
    int socket_fd;
    if((socket_fd = socket(AF_INET, SOCK_DGRAM, 0)) < 0){
        perror("socket");
        exit(1);
    }
    memset(&ifr, 0, sizeof(ifr));
    strcpy(ifr.ifr_name, "wlp2s0");
    memset(&sin, 0, sizeof(sin));
    //获取IP地址
    if(ioctl(socket_fd, SIOCGIFADDR, &ifr) != -1){
        sin = (struct sockaddr_in *)&ifr.ifr_addr;
        strcpy(ip, inet_ntoa(sin->sin_addr));
        printf("IP address is %s\n", ip);
    }
    //获取广播地址
    if(ioctl(socket_fd, SIOCGIFBRDADDR, &ifr) != -1){
        sin = (struct sockaddr_in *)&ifr.ifr_broadaddr;
        strcpy(broadcast, inet_ntoa(sin->sin_addr));
        printf("Broadcast is %s\n", broadcast);
    }
    //获取子网掩码
    if(ioctl(socket_fd, SIOCGIFNETMASK, &ifr) != -1){
        sin = (struct sockaddr_in *)&ifr.ifr_broadaddr;
        strcpy(netmask, inet_ntoa(sin->sin_addr));
        printf("Net-mask is %s\n", netmask);
    }
    //获取硬件MAC地址
    if(ioctl(socket_fd, SIOCGIFHWADDR, &ifr) != -1){
        sin = (struct sockaddr_in *)&ifr.ifr_netmask;
        sprintf(mac, "%02x:%02x:%02x:%02x:%02x:%02x",
                (unsigned char)ifr.ifr_netmask.sa_data[0],
                (unsigned char)ifr.ifr_netmask.sa_data[1],
                (unsigned char)ifr.ifr_netmask.sa_data[2],
                (unsigned char)ifr.ifr_netmask.sa_data[3],
                (unsigned char)ifr.ifr_netmask.sa_data[4],
                (unsigned char)ifr.ifr_netmask.sa_data[5]);
        printf("Mac address is %s\n", mac);
    }
     //获取硬件MTU地址
    if(ioctl(socket_fd, SIOCGIFMTU, &ifr) != -1){
        mtu = ifr.ifr_mtu;
        printf("MTU is %d\n", mtu);
    }
   return 0;
}

