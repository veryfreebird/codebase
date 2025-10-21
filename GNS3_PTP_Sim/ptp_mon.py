import requests
import subprocess
import time
import re
import socket
import os
from typing import Optional

# ==================== 配置参数 ====================
GNS3_SERVER = "http://192.168.1.100:3080"  # GNS3 控制器地址
PROJECT_NAME = "PTP_Network"                # GNS3 项目名
INTERFACE = "eth1"                          # PTP 监听的接口
UPDATE_INTERVAL = 5                         # 更新间隔（秒）

# 颜色定义
COLOR_MASTER = "00ff00"   # 绿
COLOR_SLAVE = "ff9900"    # 橙
COLOR_PASSIVE = "cccccc"  # 灰
COLOR_FAULTY = "ff0000"   # 红

# 环境变量键名（由 GNS3 注入）
GNS3_PROJECT_ID = "GNS3_PROJECT_ID"
GNS3_NODE_ID = "GNS3_NODE_ID"
GNS3_NODE_NAME = "GNS3_NODE_NAME"
# ==================================================

def get_local_ptp_role(interface: str) -> str:
    """获取本容器当前 PTP 角色"""
    try:
        result = subprocess.run(
            ["ptp4l", "-i", interface, "-m", "-S", "-f", "/etc/linuxptp/ptp4l.conf"],
            capture_output=True,
            text=True,
            timeout=10
        )
        output = result.stdout + result.stderr
        match = re.search(r"port\s+\d+:\s+state\s+(\w+)", output, re.IGNORECASE)
        if match:
            state = match.group(1).upper()
            return state if state in ["MASTER", "SLAVE", "PASSIVE"] else "FAULTY"
        return "FAULTY"
    except Exception as e:
        print(f"❌ PTP command error: {e}")
        return "FAULTY"

def get_color_for_role(role: str) -> str:
    return {
        "MASTER": COLOR_MASTER,
        "SLAVE": COLOR_SLAVE,
        "PASSIVE": COLOR_PASSIVE,
        "FAULTY": COLOR_FAULTY,
    }.get(role, COLOR_FAULTY)

def update_myself_in_gns3(project_id: str, node_id: str, role: str):
    """只更新自己的标签和颜色"""
    url = f"{GNS3_SERVER}/v2/projects/{project_id}/nodes/{node_id}"
    label_text = f"{os.getenv(GNS3_NODE_NAME, 'Unknown')} [{role}]"
    color = get_color_for_role(role)

    payload = {
        "label": {"text": label_text},
        "properties": {
            "custom_adapters": [
                {"interface": INTERFACE, "border_color": color}
            ]
        }
    }

    try:
        resp = requests.put(url, json=payload, timeout=5)
        if resp.status_code != 200:
            print(f"❌ Update failed: {resp.status_code} {resp.text}")
    except Exception as e:
        print(f"❌ Request error: {e}")

def main():
    print("🚀 Starting PTP Self-Monitor (container mode)...")

    # 从环境变量获取 GNS3 信息（GNS3 自动注入）
    project_id = os.getenv(GNS3_PROJECT_ID)
    node_id = os.getenv(GNS3_NODE_ID)
    node_name = os.getenv(GNS3_NODE_NAME)

    if not project_id or not node_id:
        print("❌ Missing GNS3 environment variables. Make sure GNS3 injects them.")
        print(f"Expected: {GNS3_PROJECT_ID}, {GNS3_NODE_ID}")
        print("You can manually set them for testing.")
        return

    print(f"✅ Running as node: {node_name} (ID: {node_id}) in project {project_id}")

    while True:
        role = get_local_ptp_role(INTERFACE)
        print(f"🔁 Current role: {role}")
        update_myself_in_gns3(project_id, node_id, role)
        time.sleep(UPDATE_INTERVAL)

if __name__ == "__main__":
    main()