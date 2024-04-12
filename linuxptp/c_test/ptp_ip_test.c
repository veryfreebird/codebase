#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <netinet/udp.h>
#include <linux/ptp_clock.h>
#include <linux/net_tstamp.h>

#define PTP_CLOCK_ID 0  // Replace with your PTP clock ID

int main() {
    // Create a socket for sending UDP packets
    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }

    // Enable PTP hardware timestamping on the socket
    int enable = 1;
    if (setsockopt(sockfd, SOL_SOCKET, SO_TIMESTAMPING, &enable, sizeof(enable)) < 0) {
        perror("setsockopt failed");
        exit(EXIT_FAILURE);
    }

    // Set the PTP clock ID for hardware timestamping
    struct ptp_clock_time ptp_time;
    memset(&ptp_time, 0, sizeof(ptp_time));
    ptp_time.clock = PTP_CLOCK_ID;
    if (setsockopt(sockfd, SOL_SOCKET, SO_TIMESTAMPING, &ptp_time, sizeof(ptp_time)) < 0) {
        perror("setsockopt failed");
        exit(EXIT_FAILURE);
    }

    // Create an IP packet
    struct iphdr ip_header;
    memset(&ip_header, 0, sizeof(ip_header));
    ip_header.ihl = 5;
    ip_header.version = 4;
    ip_header.tos = 0;
    ip_header.tot_len = sizeof(struct iphdr);
    ip_header.id = htons(12345);
    ip_header.frag_off = 0;
    ip_header.ttl = 64;
    ip_header.protocol = IPPROTO_UDP;
    ip_header.check = 0;
    ip_header.saddr = inet_addr("192.168.0.1");  // Replace with source IP address
    ip_header.daddr = inet_addr("192.168.0.2");  // Replace with destination IP address

    // Create a UDP packet
    struct udphdr udp_header;
    memset(&udp_header, 0, sizeof(udp_header));
    udp_header.source = htons(1234);
    udp_header.dest = htons(5678);
    udp_header.len = htons(sizeof(struct udphdr));
    udp_header.check = 0;

    // Send the IP packet
    struct sockaddr_in dest_addr;
    memset(&dest_addr, 0, sizeof(dest_addr));
    dest_addr.sin_family = AF_INET;
    dest_addr.sin_addr.s_addr = ip_header.daddr;
    dest_addr.sin_port = udp_header.dest;

    if (sendto(sockfd, &ip_header, sizeof(ip_header), 0, (struct sockaddr*)&dest_addr, sizeof(dest_addr)) < 0) {
        perror("sendto failed");
        exit(EXIT_FAILURE);
    }

    // Receive the hardware timestamp
    struct msghdr msg;
    memset(&msg, 0, sizeof(msg));
    struct iovec iov;
    memset(&iov, 0, sizeof(iov));
    char control[CMSG_SPACE(sizeof(struct timespec))];
    memset(control, 0, sizeof(control));
    msg.msg_control = control;
    msg.msg_controllen = sizeof(control);
    msg.msg_iov = &iov;
    msg.msg_iovlen = 1;

    char buffer[1024];
    iov.iov_base = buffer;
    iov.iov_len = sizeof(buffer);

    if (recvmsg(sockfd, &msg, 0) < 0) {
        perror("recvmsg failed");
        exit(EXIT_FAILURE);
    }

    // Extract the hardware timestamp
    struct cmsghdr *cmsg;
    struct timespec *hw_timestamp = NULL;
    for (cmsg = CMSG_FIRSTHDR(&msg); cmsg != NULL; cmsg = CMSG_NXTHDR(&msg, cmsg)) {
        if (cmsg->cmsg_level == SOL_SOCKET && cmsg->cmsg_type == SCM_TIMESTAMPING) {
            hw_timestamp = (struct timespec*)CMSG_DATA(cmsg);
            break;
        }
    }

    // Print the hardware timestamp
    if (hw_timestamp != NULL) {
        printf("Hardware timestamp: %ld.%09ld\n", hw_timestamp->tv_sec, hw_timestamp->tv_nsec);
    } else {
        printf("Hardware timestamp not found\n");
    }

    // Close the socket
    close(sockfd);

    return 0;
}