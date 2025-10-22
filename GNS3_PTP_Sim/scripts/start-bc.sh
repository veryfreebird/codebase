# start-bc.sh - 启动 PTP Boundary Clock 服务 
#!/bin/bash
CONFIG=$1

echo "Starting PTP Boundary Clock service with config: $CONFIG"

# 等待网络接口就绪
sleep 3

# 启动 ptp4l (双接口，边界时钟模式)
ptp4l -i eth0 -i eth1 -f "$CONFIG" -m -l 6 -d &

# 同步系统时钟（从上游到下游）
phc2sys -s eth0 -c eth1 -w -m -l 6 &

echo "PTP Boundary Clock started successfully"