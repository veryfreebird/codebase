#include <linux/init.h> 
#include <linux/module.h> 
//#include <net/sock.h>
#include <net/netlink.h>
#include <linux/rtnetlink.h>
#include <linux/kthread.h>
#include <linux/sched.h>


MODULE_LICENSE("GPL"); 
MODULE_AUTHOR("Ma James");

static int  mode = 0;
module_param(mode, int, S_IRUGO);
#define MAX_PAYLOAD 128

extern struct net init_net;
static struct sock *testnetlink = NULL;
//static struct task_struct * k_thread = NULL;

//netlink 消息的处理函数
static void testnetlink_rcv_skb(struct sk_buff *skb)
{
  struct nlmsghdr *nlh;
  struct sk_buff * reply_skb = NULL;
  char *data = NULL;
  char tmp[128];
  int rlen = 0, rc = 0, pid;

  if(!mode){
    printk("@@@@###############%s : %d!\n",
      __func__, __LINE__);
    memset(tmp ,0 ,sizeof(tmp));
    //receive the data from userspace
      //解析来自用户态的数据
    if (skb->len >= NLMSG_SPACE(0)) {
      //获取用户态传来的nlmsghdr数据结构
      nlh  = nlmsg_hdr(skb);
      //real data length,len - header length
      rlen = nlmsg_len(nlh);
        //获取nlmsghdr中的负载数据
      data = nlmsg_data(nlh);
          //获取发送该netlink message的进程pid
      pid = nlh->nlmsg_pid;
        
      strcpy(tmp, data);
      printk("@@@@@receive data is %s \n", 
         tmp);	
      //kfree_skb(skb);
    }

    //send packet to userspace from kernel
      //分配一个数据包， 
    reply_skb = alloc_skb(NLMSG_SPACE(MAX_PAYLOAD), GFP_ATOMIC);

    if(!reply_skb){
      printk("@@@@####reply_skb alloc error!\n");
      return ;
    }
    
        //设置netlink消息的相关参数
    nlh = nlmsg_put(reply_skb, 0,0, 0, MAX_PAYLOAD,0);
      
    //MJ.NETLINK_CB(reply_skb).pid = 0;	
    //copy netlink消息的内容
    strcpy(nlmsg_data(nlh), "netlink received!\n");
    //进行发送
    rc = netlink_unicast(testnetlink, reply_skb, pid, MSG_DONTWAIT);
    if(rc < 0){
      printk("netlink unicast error!\n");
    }
  }
  
}

struct netlink_kernel_cfg kernel_cfg;


static int testnetlink_init(void) 
{
  printk("@@@@###############!\n");
  memset(&kernel_cfg, 0, sizeof(struct netlink_kernel_cfg));
  kernel_cfg.groups = 0;
  kernel_cfg.flags = 0;
  kernel_cfg.input = testnetlink_rcv_skb;
   //在内核态创建一个netlink socket，注册相应的处理函数testnetlink_rcv_skb
//  testnetlink = netlink_kernel_create(&init_net, 27,
//      0, testnetlink_rcv_skb, NULL,
//      THIS_MODULE);
  testnetlink = netlink_kernel_create(&init_net, 27, &kernel_cfg);

  if(testnetlink == 0){
    printk("@@@@####can't create netlink socket.\n");
    return -1;
  }
  return 0; 
} 

static void testnetlink_exit(void) 
{ 
  netlink_kernel_release(testnetlink);
  printk("Goodbye, cruel world\n"); 
} 

module_init(testnetlink_init); 
module_exit(testnetlink_exit);
