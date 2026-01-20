# client.py
import requests
import base64
from requests.auth import HTTPBasicAuth

# 方法1: 使用requests的auth参数
def basic_auth_with_requests():
    url = "http://localhost:5000/protected"
    
    # 方式1: 使用HTTPBasicAuth
    response = requests.get(
        url,
        auth=HTTPBasicAuth('admin', 'admin123')
    )
    
    print("状态码:", response.status_code)
    print("响应:", response.json())
    
    # 方式2: 手动设置Authorization头
    credentials = base64.b64encode(b'admin:admin123').decode('utf-8')
    headers = {'Authorization': f'Basic {credentials}'}
    
    response2 = requests.get(url, headers=headers)
    print("\n手动设置Header:")
    print("响应:", response2.json())

# 测试不同接口
def test_all_endpoints():
    base_url = "http://localhost:5000"
    
    # 1. 公共接口（无需认证）
    print("=== 测试公共接口 ===")
    response = requests.get(f"{base_url}/public")
    print(f"状态码: {response.status_code}")
    print(f"响应: {response.json()}\n")
    
    # 2. 受保护接口（带认证）
    print("=== 测试受保护接口 ===")
    response = requests.get(
        f"{base_url}/protected",
        auth=HTTPBasicAuth('alice', 'alice456')
    )
    print(f"状态码: {response.status_code}")
    print(f"响应: {response.json()}\n")
    
    # 3. 管理员接口
    print("=== 测试管理员接口 ===")
    response = requests.get(
        f"{base_url}/admin",
        auth=HTTPBasicAuth('admin', 'admin123')
    )
    print(f"状态码: {response.status_code}")
    print(f"响应: {response.json()}\n")
    
    # 4. 普通用户访问管理员接口（应失败）
    print("=== 测试权限不足 ===")
    response = requests.get(
        f"{base_url}/admin",
        auth=HTTPBasicAuth('alice', 'alice456')
    )
    print(f"状态码: {response.status_code}")
    print(f"响应: {response.json()}\n")
    
    # 5. 用户列表
    print("=== 测试用户列表 ===")
    response = requests.get(
        f"{base_url}/users",
        auth=HTTPBasicAuth('admin', 'admin123')
    )
    print(f"状态码: {response.status_code}")
    data = response.json()
    print(f"总用户数: {data['total']}")
    for user in data['users']:
        print(f"  - {user['username']} ({user['role']})")

if __name__ == '__main__':
    test_all_endpoints()