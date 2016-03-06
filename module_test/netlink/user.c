#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <linux/if.h>
#include <linux/sockios.h>
#include <errno.h>
#include <linux/rtnetlink.h>
#include <string.h>
#define RTNL_RCV_BUF 16384
#define MAX_PAYLOAD 128
struct req{
  struct nlmsghdr nlh;
  char buf[MAX_PAYLOAD];
};

int main()
{
  int sk = 0,ret = 0;
  struct sockaddr_nl nladdr, to_nladdr;
  struct msghdr msg;
  struct nlmsghdr * nlh;
  struct iovec iov;
  struct req r;

  memset(&msg , 0 ,sizeof(struct msghdr));
  sk = socket(AF_NETLINK, SOCK_RAW, 27);
  
  if (sk == -1){
    printf("open socket error!\n");
    goto error;
  }

  memset(&nladdr, 0, sizeof(nladdr));
  //设置bind用的本地 struct sockaddr
    nladdr.nl_family = AF_NETLINK;
  nladdr.nl_groups = 0; 
  nladdr.nl_pid = getpid();
  
  //绑定本地socket
  if (bind(sk, (struct sockaddr *)&nladdr, sizeof(struct sockaddr_nl))< 0){
    printf("bind netlink socket error!\n");
    goto error;
  }
//send netlink message to kernel
  memset(&to_nladdr, 0, sizeof(to_nladdr));
  
  //设置发送用的目的sockaddr_nl
  to_nladdr.nl_family = AF_NETLINK;
  to_nladdr.nl_pid = 0;
  to_nladdr.nl_groups = 0;
  #if 0
  nlh=(struct nlmsghdr *)malloc(NLMSG_SPACE(MAX_PAYLOAD));
  nlh->nlmsg_len =NLMSG_SPACE(MAX_PAYLOAD);
  nlh->nlmsg_pid = getpid();
  nlh->nlmsg_flags = 0;

  strcpy(NLMSG_DATA(nlh), "hello ,you!");
  #else
  //设置承载负荷数据的nlmsghdr
    //包含数据和头部长度的nlmsghdr的长度
  r.nlh.nlmsg_len = NLMSG_SPACE(MAX_PAYLOAD);
  r.nlh.nlmsg_pid = getpid();
  r.nlh.nlmsg_flags = 0;
  memset(r.buf, 0, MAX_PAYLOAD);
    //设置数据
  strcpy(NLMSG_DATA(&(r.nlh)), "hello ,you!");
  #endif
    //通过iov指向要使用的nlmsghdr
  iov.iov_base = &r;
  iov.iov_len = sizeof(r);

  //设置msghdr
  msg.msg_name = &to_nladdr;
  msg.msg_namelen = sizeof(to_nladdr);
  msg.msg_iov = &iov;
  msg.msg_iovlen =1;

  //发送数据
  ret  = sendmsg(sk, &msg, 0);

  printf("@@@@@#####ret is %d, errno is %d\n", 
    ret, errno);

//receive kernel netlink message
  memset(&(r.nlh), 0 , sizeof(r));
  //接受内核发来的数据
  recvmsg(sk, &msg, 0);
  printf("@@@@######receive data from kernel is %s\n",
    NLMSG_DATA(&(r.nlh)));
  close(sk);
  return 0;
error:
  return -1;
}
