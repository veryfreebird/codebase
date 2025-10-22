#FROM ubuntu:20.04
FROM docker.xuanyuan.me/ubuntu:20.04
# 安装依赖
#RUN apt update && apt install -y \
#   git build-essential libev-dev libcap-dev iproute2 net-tools

# 编译 linuxptp
#WORKDIR /opt
#RUN git clone https://git.code.sf.net/p/linuxptp/code linuxptp
#WORKDIR /opt/linuxptp
#RUN make && make install

COPY /etc/apt/sources.list /etc/apt/sources.list

RUN apt update && apt install -y \
   iproute2 net-tools linuxptp python3 python3-pip util-linux vim sudo

#RUN pip3 install requests

# 复制配置文件和脚本
COPY configs/ /etc/ptp/
COPY entrypoint.sh /entrypoint.sh
COPY scripts/ /scripts/
COPY ptp_mon.py /scripts/ptp_mon.py

# 设置权限
RUN chmod +x /entrypoint.sh /scripts/*.sh

# 默认角色
ENV PTP_ROLE=slave
ENV PTP_PRIORITY1=128

# 启动入口
CMD ["/entrypoint.sh"]
