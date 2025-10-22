import requests
import subprocess
import time
import re
import os
from typing import Dict, List

# ==================== 配置参数 ====================
GNS3_SERVER = "http://192.168.1.100:3080"           # GNS3 控制器地址 
INTERFACES = ["eth1", "eth2"]                      # 要监控的接口列表
SOCKET_INTERFACE = "eth1"                          # socket 基于第一个接口
SOCKET_DIR = "/var/run/linuxptp"                   # socket 目录
UPDATE_INTERVAL = 5                                # 更新间隔（秒）

# 颜色定义
COLOR_MASTER = "00ff00"   # 绿
COLOR_SLAVE = "ff9900"    # 橙
COLOR_PASSIVE = "cccccc"  # 灰
COLOR_FAULTY = "ff0000"   # 红

# GNS3 注入环境变量
GNS3_PROJECT_ID = "GNS3_PROJECT_ID"
GNS3_NODE_ID = "GNS3_NODE_ID"
GNS3_NODE_NAME = "GNS3_NODE_NAME"
# ==================================================

def get_port_number(interface: str, all_interfaces: List[str]) -> int:
    """根据接口在列表中的位置返回 port number（从1开始）"""
    try:
        idx = all_interfaces.index(interface)
        return idx + 1
    except ValueError:
        print(f"❌ Interface {interface} not in INTERFACES list")
        return -1

def get_ptp_role(interface: str) -> str:
    """使用 pmc 查询指定接口的 PTP 角色"""
    sock_path = f"{SOCKET_DIR}/ptp4l.{SOCKET_INTERFACE}.sock"
    port_num = get_port_number(interface, INTERFACES)

    if port_num == -1:
        return "FAULTY"

    cmd = [
        "pmc", "-u", "-f", sock_path,
        "GET", "PORT_DATA_SET",
        f"--port={port_num}"
    ]

    try:
        result = subprocess.run(cmd, capture_output=True, text=True, timeout=10)
        if result.returncode != 0:
            print(f"⚠️ pmc failed for {interface}: {result.stderr}")
            return "FAULTY"

        match = re.search(r"port_state\s+(\w+)", result.stdout, re.IGNORECASE)
        if match:
            state = match.group(1).upper()
            return state if state in ["MASTER", "SLAVE", "PASSIVE"] else "FAULTY"
        return "FAULTY"
    except Exception as e:
        print(f"❌ Error querying {interface}: {e}")
        return "FAULTY"

def get_color_for_role(role: str) -> str:
    return {
        "MASTER": COLOR_MASTER,
        "SLAVE": COLOR_SLAVE,
        "PASSIVE": COLOR_PASSIVE,
        "FAULTY": COLOR_FAULTY,
    }.get(role, COLOR_FAULTY)

def update_node_in_gns3(project_id: str, node_id: str, roles: Dict[str, str]):
    """更新 GNS3 节点的标签和每个接口的 border_color"""
    # 构建标签文本
    role_str = ", ".join([f"{iface}:{role}" for iface, role in roles.items()])
    label_text = f"{os.getenv(GNS3_NODE_NAME, 'Node')} [{role_str}]"

    # 构建 custom_adapters 配置
    custom_adapters = []
    for i, interface in enumerate(INTERFACES):
        role = roles.get(interface, "FAULTY")
        color = get_color_for_role(role)
        custom_adapters.append({
            "interface": interface,
            "border_color": color
        })

    payload = {
        "label": {"text": label_text},
        "properties": {
            "custom_adapters": custom_adapters
        }
    }

    url = f"{GNS3_SERVER}/v2/projects/{project_id}/nodes/{node_id}"
    try:
        resp = requests.put(url, json=payload, timeout=5)
        if resp.status_code != 200:
            print(f"❌ Update failed: {resp.status_code} {resp.text}")
    except Exception as e:
        print(f"❌ Request error: {e}")

def main():
    print("🚀 Starting Multi-Port PTP Monitor...")

    project_id = os.getenv(GNS3_PROJECT_ID)
    node_id = os.getenv(GNS3_NODE_ID)
    node_name = os.getenv(GNS3_NODE_NAME)

    if not project_id or not node_id:
        print("❌ Missing GNS3 environment variables.")
        return

    print(f"✅ Monitoring interfaces: {INTERFACES}")
    print(f"✅ Using socket: ptp4l.{SOCKET_INTERFACE}.sock")
    print(f"✅ Running as: {node_name} (ID: {node_id})")

    while True:
        roles = {}
        for iface in INTERFACES:
            role = get_ptp_role(iface)
            roles[iface] = role
            print(f"🔁 {iface}: {role}")

        update_node_in_gns3(project_id, node_id, roles)
        time.sleep(UPDATE_INTERVAL)

if __name__ == "__main__":
    main()