#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <errno.h>
#include <net/if.h>
#include <linux/ptp_clock.h>
#include <linux/time.h>

int main() {
    int sockfd;
    struct sockaddr_in servaddr;
    struct ptp_clock_request request;
    struct timespec ts;
    char buffer[1024];
    socklen_t len = sizeof(servaddr);

    // Create a TCP socket
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("socket");
        return -1;
    }

    // Set the server address
    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(12345);
    inet_pton(AF_INET, "192.168.1.1", &servaddr.sin_addr);

    // Connect to the server
    if (connect(sockfd, (struct sockaddr *)&servaddr, len) < 0) {
        perror("connect");
        close(sockfd);
        return -1;
    }
    

    memcpy(&ts, &request.ts, sizeof(ts));

    // Set the PTP clock request
    memset(&request, 0, sizeof(request));
    request.type = PTP_CLOCK_REQUEST_GET_STIME;

    // Send the PTP clock request
    if (send(sockfd, &request, sizeof(request), 0) < 0) {
        perror("send");
        close(sockfd);
        return -1;
    }

    // Receive the PTP clock response
    if (recv(sockfd, buffer, sizeof(buffer), 0) < 0) {
        perror("recv");
        close(sockfd);
        return -1;
    }

    // Parse the PTP clock response
    struct ptp_clock_response *response = (struct ptp_clock_response *)buffer;
    ts.tv_sec = response->st.sec;
    ts.tv_nsec = response->st.nsec;

    // Print the time stamp
    std::cout << "Time stamp: " << ts.tv_sec << "." << ts.tv_nsec << std::endl;

    // Close the socket
    close(sockfd);

    return 0;
}