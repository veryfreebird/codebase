# start-master.sh - 启动 PTP Master 服务 
#!/bin/bash
CONFIG=$1

echo "Starting PTP Master service with config: $CONFIG"

# 等待网络接口就绪
sleep 3

# 启动 ptp4l (Master 模式)
ptp4l -i eth0 -f "$CONFIG" -m -l 6 -s &

# 同步系统时钟到 PHC
#phc2sys -s eth0 -w -m -l 6 &

echo "PTP Master started successfully"