# start-tc.sh - 启动 PTP Transparent Clock 服务 
#!/bin/bash
CONFIG=$1

echo "Starting PTP Transparent Clock service with config: $CONFIG"

# 等待网络接口就绪
sleep 3

# 启动 ptp4l (双接口，透明时钟模式)
ptp4l -i eth0 -i eth1 -f "$CONFIG" -m -l 6 &

echo "PTP Transparent Clock started successfully"