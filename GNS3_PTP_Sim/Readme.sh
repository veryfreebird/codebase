# 构建和使用说明
#!/bin/bash

echo "=== PTP Docker 镜像构建说明 ==="
echo "1. 构建镜像："
echo "   docker build -t my-ptp-node:latest ."
echo ""
echo "2. 在 GNS3 中创建模板："
echo "   - 使用镜像: my-ptp-node:latest"
echo "   - 网络适配器: 2个 (兼容 BC/TC)"
echo "   - 环境变量示例:"
echo "     PTP_ROLE=master"
echo "     PTP_PRIORITY1=10"
echo ""
echo "3. 角色配置示例："
echo "   Master: PTP_ROLE=master, PTP_PRIORITY1=10"
echo "   Slave:  PTP_ROLE=slave"
echo "   BC:     PTP_ROLE=bc, PTP_PRIORITY1=128"
echo "   TC:     PTP_ROLE=tc"
echo ""
echo "4. 启动后检查日志："
echo "   docker logs <container_id>"
echo ""
echo "5. 在容器内验证："
echo "   ptp4l -i eth0 -f /etc/ptp/master.cfg -m"
echo "   pmc -u -b 0 'GET TIME_STATUS_NP'"

sudo docker run -it ubuntu:latest /bin/bash
sudo docker exec -it <容器ID> /bin/bash
echo $HOME
printenv
