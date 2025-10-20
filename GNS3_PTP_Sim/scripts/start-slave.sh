# start-slave.sh - 启动 PTP Slave 服务
#!/bin/bash
CONFIG=$1

echo "Starting PTP Slave service with config: $CONFIG"

# 等待网络接口就绪
sleep 3

# 启动 ptp4l (Slave 模式)
ptp4l -i eth0 -f "$CONFIG" -m -l 6 -d &

# 同步系统时钟到 PHC
phc2sys -s eth0 -w -m -l 6 &

echo "PTP Slave started successfully"