Linux Bond Test
==

# Topology #


----------------------------       ------------------------
|                  |-eth0-1_|______|_eth1-0-|              |
| default ns bond0-|        |      |        |-bond0 test ns|
|                  |-eth2-3_|______|_eth3-2-|              |
----------------------------       ------------------------

# Bond Mode #
mode=0 (Balance Round Robin) per packet **balance-rr**

mode=1 (Active backup) **active-backup**

mode=2 (Balance XOR) **balance-xor**

mode=3 (Broadcast) **broadcast**

mode=4 (802.3ad) **802.3ad**

mode=5 (Balance TLB) **balance-tlb**

mode=6 (Balance ALB) **balance-alb**

# Bond Create #
```
##modprobe bonding mode=802.3ad miimon=100
##modprobe bonding mode=802.3ad
##modprobe bonding mode=balance-rr miimon=100
##modprobe bonding mode=active-backup miimon=100
modprobe bonding mode=802.3ad miimon=100
modprobe e100
ip netns add test
ip link add eth0-1 type veth peer name eth1-0
ip link add eth2-3 type veth peer name eth3-2
ip link set eth1-0 netns test
ip link set eth3-2 netns test

default ns: 

echo +bond0 > /sys/class/net/bonding_masters
ifconfig bond0 up
ifenslave bond0 eth0-1 eth2-3
ip addr add 111.111.111.111/24 dev bond0

test ns: 

ip netns exec test ip link add bond0 type bond
ip netns exec test ifconfig bond0 up
ip netns exec test ifenslave bond0 eth1-0 eth3-2
ip netns exec test ip addr add 111.111.111.112/24 dev bond0

verify: 
ifconfig
ip netns exec test ifconfig
cat /proc/net/bonding/bond0
ip netns exec test cat /proc/net/bonding/bond0
ping 111.111.111.112 -I 111.111.111.111

change active:
 ifenslave -c bond0 eth2-3
```

# cleanup #
```
rmmod bonding
ifconfig bond0 down
ip link del bond0
ip netns exec test ifconfig bond0 down
ip netns exec test ip link del bond0
```

mode=0 (Balance Round Robin) per packet
mode=1 (Active backup)
mode=2 (Balance XOR)
mode=3 (Broadcast)
mode=4 (802.3ad)
mode=5 (Balance TLB)
mode=6 (Balance ALB)
Modes of bonding :
RHEL bonding supports 7 possible “modes” for bonded interfaces. These modes determine the way in which traffic 
sent out of the bonded interface is actually dispersed over the real interfaces. 

**Modes 0, 1, and 2 are by far the most commonly used among them.**

**Mode 0 (balance-rr)**
This mode transmits packets in a sequential order from the first available slave through the last. If two real 
interfaces are slaves in the bond and two packets arrive destined out of the bonded interface the first will 
be transmitted on the first slave and the second frame will be transmitted on the second slave. The third 
packet will be sent on the first and so on. This provides load balancing and fault tolerance.

**Mode 1 (active-backup)**
Mode 1 places one of the interfaces into a backup state and will only make it active if the link is lost by the 
active interface. **Only one slave in the bond is active at an instance of time. A different slave becomes active only when the active slave fails.** This mode provides fault tolerance.

**Mode 2 (balance-xor)**
Transmits based on XOR formula. (Source MAC address is XOR’d with destination MAC address) modula slave count. 
This selects the same slave for each destination MAC address and provides load balancing and fault tolerance.

Mode 3 (broadcast)
The broadcast mode transmits everything on all slave interfaces. This mode is least used (only for a specific 
purpose) and provides only fault tolerance.

Mode 4 (802.3ad)
The 802.3ad mode is known as Dynamic Link Aggregation mode. It creates aggregation groups that share the same 
speed and duplex settings. This mode requires a switch that supports IEEE 802.3ad Dynamic link. Slave selection 
for outgoing traffic is done according to the transmit hash policy, which may be changed from the default 
simple XOR policy via the xmit_hash_policy option. Note that not all transmit policies may be 802.3ad compliant,particularly in regards to the packet mis-ordering requirements of section 43.2.4 of the 802.3ad standard. 
Differing peer implementations will have varying tolerances for noncompliance.

Mode 5 (balance-tlb)
This is called as Adaptive transmit load balancing. The outgoing traffic is distributed according to the current load and queue on each slave interface. Incoming traffic is received by the current slave.

Mode 6 (balance-alb)
This is Adaptive load balancing mode. This includes balance-tlb + receive load balancing (rlb) for IPV4 traffic. The receive load balancing is achieved by ARP negotiation. The bonding driver intercepts the ARP Replies sent by the server on their way out and overwrites the src hw address with the unique hw address of one of the slaves in the bond such that different clients use different hw addresses for the server.




https://access.redhat.com/documentation/en-us/red_hat_enterprise_linux/7/html/networking_guide/sec-using_channel_bonding

balance-rr or 0 — Sets a round-robin policy for fault tolerance and load balancing. Transmissions are received and sent out sequentially on each bonded slave interface beginning with the first one available.

active-backup or 1 — Sets an active-backup policy for fault tolerance. **Transmissions are received and sent out through the first available bonded slave interface.** Another bonded slave interface is only used if the active bonded slave interface fails.

balance-xor or 2 — Transmissions are based on the selected hash policy. The default is to derive a hash by XOR of the source and destination MAC addresses multiplied by the modulo of the number of slave interfaces. In this mode traffic destined for specific peers will always be sent over the same interface. As the destination is determined by the MAC addresses this method works best for traffic to peers on the same link or local network. If traffic has to pass through a single router then this mode of traffic balancing will be suboptimal.

broadcast or 3 — Sets a broadcast policy for fault tolerance. All transmissions are sent on all slave interfaces.

802.3ad or 4 — Sets an IEEE 802.3ad dynamic link aggregation policy. Creates aggregation groups that share the same speed and duplex settings. Transmits and receives on all slaves in the active aggregator. Requires a switch that is 802.3ad compliant.

balance-tlb or 5 — Sets a Transmit Load Balancing (TLB) policy for fault tolerance and load balancing. The outgoing traffic is distributed according to the current load on each slave interface. Incoming traffic is received by the current slave. If the receiving slave fails, another slave takes over the MAC address of the failed slave. This mode is only suitable for local addresses known to the kernel bonding module and therefore cannot be used behind a bridge with virtual machines.

balance-alb or 6 — Sets an Adaptive Load Balancing (ALB) policy for fault tolerance and load balancing. Includes transmit and receive load balancing for IPv4 traffic. Receive load balancing is achieved through ARP negotiation. This mode is only suitable for local addresses known to the kernel bonding module and therefore cannot be used behind a bridge with virtual machines.

## xmit_hash_policy=value ##
Selects the transmit hash policy used for slave selection in balance-xor and 802.3ad modes. Possible values are: 

• 0 or layer2 — Default setting. This parameter uses the XOR of hardware MAC addresses to generate the hash. The formula used is: 
```
(source_MAC_address XOR destination_MAC) MODULO slave_count
```

This algorithm will place all traffic to a particular network peer on the same slave, and is 802.3ad compliant. 

• 1 or layer3+4 — Uses upper layer protocol information (when available) to generate the hash. This allows for traffic to a particular network peer to span multiple slaves, although a single connection will not span multiple slaves. 

The formula for unfragmented TCP and UDP packets used is: 
```
((source_port XOR dest_port) XOR
  ((source_IP XOR dest_IP) AND 0xffff)
    MODULO slave_count
```

For fragmented TCP or UDP packets and all other IP protocol traffic, the source and destination port information is omitted. For non-IP traffic, the formula is the same as the layer2 transmit hash policy. 

This policy intends to mimic the behavior of certain switches; particularly, Cisco switches with PFC2 as well as some Foundry and IBM products. 

**The algorithm used by this policy is not 802.3ad compliant.**


• 2 or layer2+3 — Uses a combination of layer2 and layer3 protocol information to generate the hash. 

Uses XOR of hardware MAC addresses and IP addresses to generate the hash. The formula is: 
```
(((source_IP XOR dest_IP) AND 0xffff) XOR
  ( source_MAC XOR destination_MAC ))
    MODULO slave_count
```
This algorithm will place all traffic to a particular network peer on the same slave. For non-IP traffic, the formula is the same as for the layer2 transmit hash policy. 

This policy is intended to provide a more balanced distribution of traffic than layer2 alone, especially in environments where a layer3 gateway device is required to reach most destinations. 

**This algorithm is 802.3ad compliant.**



























https://www.kernel.org/doc/Documentation/networking/bonding.txt
