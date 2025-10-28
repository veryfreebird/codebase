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

find /opt/gns3 -name "*.gns3template" -type f

sudo nano /opt/gns3/templates/docker_my_ubuntu_netadmin_latest.gns3template
在文件中添加：

json
编辑
{
  "category": "guest",
  "compute_id": "vm",
  "console_type": "telnet",
  "default_name_format": "container{0}",
  "image": "my-ubuntu-netadmin:latest",
  "name": "Ubuntu NetAdmin",
  "extra_container_options": "--cap-add=SYS_ADMIN --cap-add=SYS_TIME",
  ...
}

#!/bin/bash
CONTAINER_ID=$(docker ps -q --filter "name=gns3-您的容器")
docker update --cap-add SYS_ADMIN --cap-add SYS_TIME $CONTAINER_ID

修改 Docker 守护进程配置​​
# 编辑 Docker 配置
sudo nano /etc/docker/daemon.json
{
  "default-capabilities": ["SYS_ADMIN", "SYS_TIME"]
}

（2）修改 Docker 服务配置（不推荐）​​
通过覆盖 Docker 服务参数 ​​全局生效​​（但影响所有容器）：
# 编辑 systemd 配置
sudo nano /etc/systemd/system/docker.service.d/override.conf
添加：
[Service]
ExecStart=
ExecStart=/usr/bin/dockerd --default-cap-add SYS_ADMIN --default-cap-add SYS_TIME

修改 Docker 默认运行时​​
# 编辑 /etc/docker/daemon.json
{
  "default-runtime": "gns3-custom",  # 强制所有容器使用自定义运行时
  "runtimes": {
    "gns3-custom": {
      "path": "/usr/local/bin/gns3-docker-wrapper",
      "runtimeArgs": []
    }
  }
}

sudo tee /usr/local/bin/gns3-docker-wrapper <<'EOF'
#!/bin/bash
# 拦截所有 GNS3 启动的容器，自动添加权限
if echo "$@" | grep -q "com.docker.compose.project=gns3"; then
  exec /usr/bin/runc --cap-add SYS_ADMIN --cap-add SYS_TIME "$@"
else
  exec /usr/bin/runc "$@"
fi
EOF

sudo chmod +x /usr/local/bin/gns3-docker-wrapper

/etc/docker/daemon.json​​
{
  "registry-mirrors": [
    "https://<your-mirror-id>.mirror.aliyuncs.com"
  ],
  "default-runtime": "runc",
  "runtimes": {
    "runc": {
      "path": "/usr/bin/runc",
      "runtimeArgs": ["--cap-add=SYS_ADMIN", "--cap-add=SYS_TIME"]
    }
  }
}