#include <errno.h>
#include <error.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <linux/if.h>
#include <linux/netlink.h>
#include <linux/rtnetlink.h>


#define NIPQUAD(addr) \
    ((unsigned char *)&addr)[0], \
((unsigned char *)&addr)[1], \
((unsigned char *)&addr)[2], \
((unsigned char *)&addr)[3]

#define NIPQUAD_FMT "%u.%u.%u.%u"

#define NIP6(addr) \
    ntohs((addr).s6_addr16[0]), \
ntohs((addr).s6_addr16[1]), \
ntohs((addr).s6_addr16[2]), \
ntohs((addr).s6_addr16[3]), \
ntohs((addr).s6_addr16[4]), \
ntohs((addr).s6_addr16[5]), \
ntohs((addr).s6_addr16[6]), \
ntohs((addr).s6_addr16[7])

#define NIP6_FMT "%04x:%04x:%04x:%04x:%04x:%04x:%04x:%04x"

#define INFINITY_LIFE_TIME      0xFFFFFFFFU

main()

{
    struct {
        struct nlmsghdr n;
        struct ifaddrmsg r;
        char             buf[1024];                
    } req;

    struct rtattr *rta;
    struct sockaddr_in6 *sin6p;
    struct sockaddr_in *sinp;
    int status;
    char buf[16384];
    struct nlmsghdr *nlmp;
    struct ifaddrmsg *rtmp;
    struct rtattr *rtatp;
    int rtattrlen;
    struct in_addr *inp;
    struct in6_addr *in6p;
    struct ifa_cacheinfo *cache_info;

    int fd = socket(PF_NETLINK, SOCK_DGRAM, NETLINK_ROUTE);

    /* We use RTM_GETADDR to fetch the ip address from the kernel interface table *
     * So what we do here is pretty simple, we populate the msg structure (req)   *
     * the size of the message buffer is specified to netlink message header, and *
     * flags values are set as NLM_F_ROOT | NLM_F_REQUEST. The request flag must  *
     * be set for all messages requesting the data from kernel. The root flag is  *
     * used to notify the kernel to return the full tabel. Another flag (not used)*
     * is NLM_F_MATCH. This is used to get only speficed entried in the table.    *
     * At the time of writing this program this flag is not implemented in kernel */

    memset(&req, 0, sizeof(req));
    req.n.nlmsg_len = NLMSG_LENGTH(sizeof(struct ifaddrmsg));
    req.n.nlmsg_flags = NLM_F_REQUEST | NLM_F_ROOT;
    req.n.nlmsg_type = RTM_GETADDR;


    /* AF_INET6 is used to signify the kernel to fetch only ipv6 entires.         *
     * Replacing this with AF_INET will fetch ipv4 address table.                 */

    req.r.ifa_family = AF_INET6;

    /* Fill up all the attributes for the rtnetlink header. The code is pretty easy*
     * to understand. The lenght is very important. We use 16 to signify the ipv6  *
     * address. If the user chooses to use AF_INET (ipv4) the length has to be     *
     * RTA_LENGTH(4) */

    rta = (struct rtattr *)(((char *)&req) + NLMSG_ALIGN(req.n.nlmsg_len));
    rta->rta_len = RTA_LENGTH(16);

    /* Time to send and recv the message from kernel */

    status = send(fd, &req, req.n.nlmsg_len, 0);

    if (status < 0) {
        perror("send");
        return 1;
    }

    status = recv(fd, buf, sizeof(buf), 0);

    if (status < 0) {
        perror("recv");
        return 1;
    }

    if(status == 0){
        printf("EOF\n");
        return 1;
    }

    /* Typically the message is stored in buf, so we need to parse the message to *
     * get the required data for our display. */

        for(nlmp = (struct nlmsghdr *)buf; status > sizeof(*nlmp);){
            int len = nlmp->nlmsg_len;
            int req_len = len - sizeof(*nlmp);

            if (req_len<0 || len>status) {
                printf("error\n");
                return -1;
            }

            if (!NLMSG_OK(nlmp, status)) {
                printf("NLMSG not OK\n");
                return 1;
            }

            rtmp = (struct ifaddrmsg *)NLMSG_DATA(nlmp);
            rtatp = (struct rtattr *)IFA_RTA(rtmp);

            /* Start displaying the index of the interface */

            printf("Index Of Iface= %d\n",rtmp->ifa_index);

            rtattrlen = IFA_PAYLOAD(nlmp);

            for (; RTA_OK(rtatp, rtattrlen); rtatp = RTA_NEXT(rtatp, rtattrlen)) {

                /* Here we hit the fist chunk of the message. Time to validate the    *
                 * the type. For more info on the different types see man(7) rtnetlink*
                 * The table below is taken from man pages.                           *
                 * Attributes                                                         *
                 * rta_type        value type             description                 *
                 * -------------------------------------------------------------      *
                 * IFA_UNSPEC      -                      unspecified.                *
                 * IFA_ADDRESS     raw protocol address   interface address           *
                 * IFA_LOCAL       raw protocol address   local address               *
                 * IFA_LABEL       asciiz string          name of the interface       *
                 * IFA_BROADCAST   raw protocol address   broadcast address.          *
                 * IFA_ANYCAST     raw protocol address   anycast address             *
                 * IFA_CACHEINFO   struct ifa_cacheinfo   Address information.        */

                if(rtatp->rta_type == IFA_CACHEINFO){
                    cache_info = (struct ifa_cacheinfo *)RTA_DATA(rtatp);
                    if (cache_info->ifa_valid == INFINITY_LIFE_TIME)
                        printf("valid_lft forever\n");
                    else
                        printf("valid_lft %usec\n", cache_info->ifa_valid);

                    if (cache_info->ifa_prefered == INFINITY_LIFE_TIME)
                        printf(" preferred_lft forever\n");
                    else
                        printf(" preferred_lft %usec\n",cache_info->ifa_prefered);
                }

                /* NOTE: All the commented code below can be used as it is for ipv4 table */

                if(rtatp->rta_type == IFA_ADDRESS){
                    // inp = (struct in_addr *)RTA_DATA(rtatp);
                    in6p = (struct in6_addr *)RTA_DATA(rtatp);
                    printf("addr0: " NIP6_FMT "\n",NIP6(*in6p));
                    // printf("addr0: "NIPQUAD_FMT"\n",NIPQUAD(*inp));
                }

                if(rtatp->rta_type == IFA_LOCAL){
                    // inp = (struct in_addr *)RTA_DATA(rtatp);
                    in6p = (struct in6_addr *)RTA_DATA(rtatp);
                    printf("addr1: " NIP6_FMT "\n",NIP6(*in6p));
                    // printf("addr1: "NIPQUAD_FMT"\n",NIPQUAD(*inp));
                }

                if(rtatp->rta_type == IFA_BROADCAST){
                    // inp = (struct in_addr *)RTA_DATA(rtatp);
                    in6p = (struct in6_addr *)RTA_DATA(rtatp);
                    printf("bcataddr: " NIP6_FMT "\n",NIP6(*in6p));
                    // printf("Bcast addr: "NIPQUAD_FMT"\n",NIPQUAD(*inp));
                }

                if(rtatp->rta_type == IFA_ANYCAST){
                    //inp = (struct in_addr *)RTA_DATA(rtatp);
                    in6p = (struct in6_addr *)RTA_DATA(rtatp);
                    printf("anycastaddr: "NIP6_FMT"\n",NIP6(*in6p));
                    // printf("anycast addr: "NIPQUAD_FMT"\n",NIPQUAD(*inp));
                }

            }
            status -= NLMSG_ALIGN(len);
            nlmp = (struct nlmsghdr*)((char*)nlmp + NLMSG_ALIGN(len));

        }

}


