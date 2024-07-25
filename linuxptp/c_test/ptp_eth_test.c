#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <linux/if_packet.h>
#include <net/ethernet.h>
#include <net/if.h>
#include <netinet/ip.h>
#include <netinet/udp.h>
#include <netinet/ether.h>
#include <arpa/inet.h>
#include <unistd.h>

#define PTP_EVENT_PORT 319
#define PTP_GENERAL_PORT 320

int main() {
    int sock;
    struct sockaddr_ll sa;
    struct ifreq ifr;
    char ifname[] = "eth0"; // Replace with your interface name

    // Create a raw socket for PTP packets
    sock = socket(AF_PACKET, SOCK_RAW, htons(ETH_P_ALL));
    if (sock == -1) {
        perror("socket");
        exit(1);
    }

    // Set the network interface index
    memset(&ifr, 0, sizeof(ifr));
    strncpy(ifr.ifr_name, ifname, IFNAMSIZ - 1);
    if (ioctl(sock, SIOCGIFINDEX, &ifr) == -1) {
        perror("ioctl");
        close(sock);
        exit(1);
    }

    // Bind the socket to the network interface
    memset(&sa, 0, sizeof(sa));
    sa.sll_family = AF_PACKET;
    sa.sll_protocol = htons(ETH_P_ALL);
    sa.sll_ifindex = ifr.ifr_ifindex;
    if (bind(sock, (struct sockaddr *)&sa, sizeof(sa)) == -1) {
        perror("bind");
        close(sock);
        exit(1);
    }

    // Enable hardware timestamping
    int enable = 1;
    if (setsockopt(sock, SOL_SOCKET, SO_TIMESTAMPING, &enable, sizeof(enable)) == -1) {
        perror("setsockopt");
        close(sock);
        exit(1);
    }

    // Receive and process PTP packets
    while (1) {
        char buffer[ETH_FRAME_LEN];
        struct msghdr msg;
        struct iovec iov;
        struct timespec ts[3];

        memset(&msg, 0, sizeof(msg));
        memset(&iov, 0, sizeof(iov));

        iov.iov_base = buffer;
        iov.iov_len = sizeof(buffer);

        msg.msg_iov = &iov;
        msg.msg_iovlen = 1;
        msg.msg_control = ts;
        msg.msg_controllen = sizeof(ts);

        ssize_t len = recvmsg(sock, &msg, 0);
        if (len == -1) {
            perror("recvmsg");
            close(sock);
            exit(1);
        }

        // Extract the hardware timestamp
        struct timespec *hwts = NULL;
        for (struct cmsghdr *cmsg = CMSG_FIRSTHDR(&msg); cmsg != NULL; cmsg = CMSG_NXTHDR(&msg, cmsg)) {
            if (cmsg->cmsg_level == SOL_SOCKET && cmsg->cmsg_type == SO_TIMESTAMPING) {
                hwts = (struct timespec *)CMSG_DATA(cmsg);
                break;
            }
        }

        // Process the PTP packet and timestamp
        if (hwts != NULL) {
            // TODO: Process the PTP packet and use the hardware timestamp
            printf("Received PTP packet with hardware timestamp: %ld.%09ld\n", hwts->tv_sec, hwts->tv_nsec);
        }
    }

    close(sock);
    return 0;
}



/*Send packets and retrieve hardware timestamp*/
/*Start of sending*/
int ts_opt = SOF_TIMESTAMPING_TX_HARDWARE | SOF_TIMESTAMPING_RX_HARDWARE | SOF_TIMESTAMPING_RAW_HARDWARE;
if (setsockopt(sock, SOL_SOCKET, SO_TIMESTAMPING, &ts_opt, sizeof(ts_opt)) < 0) {
    perror("setsockopt");
    exit(1);
}
struct msghdr msg = {0};
struct iovec iov = { buffer, sizeof(buffer) };
msg.msg_iov = &iov;
msg.msg_iovlen = 1;
if (sendmsg(sock, &msg, 0) == -1) {
    perror("sendmsg");
    exit(1);
}
char control[256];
struct msghdr msg = {0};
struct iovec iov = { buffer, sizeof(buffer) };
msg.msg_iov = &iov;
msg.msg_iovlen = 1;
msg.msg_control = control;
msg.msg_controllen = sizeof(control);
if (recvmsg(sock, &msg, MSG_ERRQUEUE) == -1) {
    perror("recvmsg");
    exit(1);
}
struct timespec *hwts = NULL;
for (struct cmsghdr *cmsg = CMSG_FIRSTHDR(&msg); cmsg != NULL; cmsg = CMSG_NXTHDR(&msg, cmsg)) {
    if (cmsg->cmsg_level == SOL_SOCKET && cmsg->cmsg_type == SO_TIMESTAMPING) {
        hwts = (struct timespec *)CMSG_DATA(cmsg);
        break;
    }
}
if (hwts != NULL) {
    printf("Sent PTP packet with hardware timestamp: %ld.%09ld\n", hwts->tv_sec, hwts->tv_nsec);
}
/*End of sending*/