#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <linux/if_packet.h>
#include <net/ethernet.h>
#include <net/if.h>
#include <netinet/ip.h>
#include <netinet/udp.h>
#include <arpa/inet.h>

#define INTERFACE_NAME "eth0"
#define PTP_HEADER_SIZE 34

int main() {
    int sockfd;
    struct sockaddr_ll sa;
    struct ifreq ifr;
    char buffer[ETH_FRAME_LEN];
    
    // Create a raw socket
    sockfd = socket(AF_PACKET, SOCK_RAW, htons(ETH_P_ALL));
    if (sockfd == -1) {
        perror("socket");
        exit(EXIT_FAILURE);
    }
    
    // Set the network interface index
    memset(&ifr, 0, sizeof(struct ifreq));
    strncpy(ifr.ifr_name, INTERFACE_NAME, IFNAMSIZ - 1);
    if (ioctl(sockfd, SIOCGIFINDEX, &ifr) == -1) {
        perror("ioctl");
        close(sockfd);
        exit(EXIT_FAILURE);
    }
    
    // Set socket address structure
    memset(&sa, 0, sizeof(struct sockaddr_ll));
    sa.sll_family = AF_PACKET;
    sa.sll_protocol = htons(ETH_P_ALL);
    sa.sll_ifindex = ifr.ifr_ifindex;
    
    // Bind the socket to the network interface
    if (bind(sockfd, (struct sockaddr *)&sa, sizeof(struct sockaddr_ll)) == -1) {
        perror("bind");
        close(sockfd);
        exit(EXIT_FAILURE);
    }
    
    while (1) {
        ssize_t numBytes = recv(sockfd, buffer, ETH_FRAME_LEN, 0);
        if (numBytes == -1) {
            perror("recv");
            close(sockfd);
            exit(EXIT_FAILURE);
        }
        
        // Extract PTP timestamp from the Ethernet frame
        if (numBytes >= PTP_HEADER_SIZE) {
            struct ether_header *ethHeader = (struct ether_header *)buffer;
            struct iphdr *ipHeader = (struct iphdr *)(buffer + sizeof(struct ether_header));
            struct udphdr *udpHeader = (struct udphdr *)(buffer + sizeof(struct ether_header) + sizeof(struct iphdr));
            char *ptpHeader = buffer + sizeof(struct ether_header) + sizeof(struct iphdr) + sizeof(struct udphdr);
            
            // Check if the packet is a PTP packet
            if (ethHeader->ether_type == htons(ETHERTYPE_IP) &&
                ipHeader->protocol == IPPROTO_UDP &&
                udpHeader->dest == htons(319)) {
                
                // Extract the PTP timestamp from the PTP header
                // You can access the PTP timestamp fields here and use them as needed
                
                // Example: Print the PTP timestamp
                printf("PTP Timestamp: %02x:%02x:%02x:%02x:%02x:%02x\n",
                       ptpHeader[0], ptpHeader[1], ptpHeader[2],
                       ptpHeader[3], ptpHeader[4], ptpHeader[5]);
            }
        }
    }
    
    close(sockfd);
    return 0;
}