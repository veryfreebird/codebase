import socket
import struct

##only work on linux platform

# 定义netlink消息类型
NLMSG_NOOP = 0x1
NLMSG_ERROR = 0x2
NLMSG_DONE = 0x3
NLMSG_OVERRUN = 0x4
RTMGRP_LINK = 0x1

# 定义netlink消息头部结构
class nlmsghdr(struct.Struct):
    def __init__(self):
        self.format = "IHHII"
        self.length = struct.calcsize(self.format)

    def pack(self, nlmsg_len, nlmsg_type, nlmsg_flags, nlmsg_seq, nlmsg_pid):
        return struct.pack(self.format, nlmsg_len, nlmsg_type, nlmsg_flags, nlmsg_seq, nlmsg_pid)

    def unpack(self, data):
        return struct.unpack(self.format, data)

# 定义netlink链接状态消息结构
class ifinfomsg(struct.Struct):
    def __init__(self):
        self.format = "BBHII"
        self.length = struct.calcsize(self.format)

    def pack(self, ifi_family, ifi_type, ifi_index, ifi_flags, ifi_change):
        return struct.pack(self.format, ifi_family, ifi_type, ifi_index, ifi_flags, ifi_change)

    def unpack(self, data):
        return struct.unpack(self.format, data)

# 创建netlink socket
sock = socket.socket(socket.AF_NETLINK, socket.SOCK_RAW, socket.NETLINK_ROUTE)

# 绑定netlink socket到RTMGRP_LINK组
sock.bind((0, RTMGRP_LINK))

while True:
    data = sock.recv(4096)
    nlmsg_len, nlmsg_type, nlmsg_flags, nlmsg_seq, nlmsg_pid = nlmsghdr().unpack(data[:nlmsghdr().length])
    if nlmsg_type == NLMSG_DONE:
        break
    elif nlmsg_type == NLMSG_ERROR:
        print("Netlink error")
        break
    elif nlmsg_type == NLMSG_OVERRUN:
        print("Netlink message overrun")
        break
    elif nlmsg_type == RTMGRP_LINK:
        ifi_family, ifi_type, ifi_index, ifi_flags, ifi_change = ifinfomsg().unpack(data[nlmsghdr().length:])
        if ifi_change & 0x1000:  # IFF_RUNNING flag changed
            if ifi_flags & 0x100:  # IFF_UP flag set
                print(f"Interface {ifi_index} is up")
            else:
                print(f"Interface {ifi_index} is down")