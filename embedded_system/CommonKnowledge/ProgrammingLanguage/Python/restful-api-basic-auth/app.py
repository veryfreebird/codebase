# app.py
import base64
from functools import wraps
from flask import Flask, request, jsonify, make_response
from flask_httpauth import HTTPBasicAuth
from werkzeug.security import generate_password_hash, check_password_hash
import bcrypt
import os
from dotenv import load_dotenv

# 加载环境变量
load_dotenv()

app = Flask(__name__)
auth = HTTPBasicAuth()

# 用户数据库（生产环境使用真实数据库）
users_db = {
    "admin": {
        "password_hash": generate_password_hash("admin123"),
        "role": "admin",
        "email": "admin@example.com"
    },
    "alice": {
        "password_hash": generate_password_hash("alice456"),
        "role": "user", 
        "email": "alice@example.com"
    },
    "bob": {
        "password_hash": generate_password_hash("bob789"),
        "role": "user",
        "email": "bob@example.com"
    }
}

# 使用bcrypt增强安全性（可选）
bcrypt_users = {
    "secure_user": {
        "password_hash": bcrypt.hashpw("secure123".encode(), bcrypt.gensalt()).decode(),
        "role": "admin"
    }
}

# 验证回调函数
@auth.verify_password
def verify_password(username, password):
    """验证用户名和密码"""
    if username in users_db:
        stored_hash = users_db[username]["password_hash"]
        return check_password_hash(stored_hash, password)
    elif username in bcrypt_users:
        stored_hash = bcrypt_users[username]["password_hash"]
        return bcrypt.checkpw(password.encode(), stored_hash.encode())
    return False

@auth.get_user_roles
def get_user_roles(username):
    """获取用户角色"""
    if username in users_db:
        return users_db[username]["role"]
    elif username in bcrypt_users:
        return bcrypt_users[username]["role"]
    return "guest"

# 手动解析Basic Auth（了解原理）
def parse_basic_auth():
    """手动解析Basic Auth头部"""
    auth_header = request.headers.get('Authorization')
    
    if not auth_header or not auth_header.startswith('Basic '):
        return None, None
    
    # 移除'Basic '前缀
    encoded_credentials = auth_header.split(' ')[1]
    
    try:
        # Base64解码
        decoded_bytes = base64.b64decode(encoded_credentials)
        decoded_str = decoded_bytes.decode('utf-8')
        
        # 分割用户名和密码
        username, password = decoded_str.split(':', 1)
        return username, password
    except Exception as e:
        return None, None

# 自定义装饰器：角色验证
def role_required(required_role):
    def decorator(f):
        @wraps(f)
        def decorated_function(*args, **kwargs):
            # 手动验证
            username, password = parse_basic_auth()
            
            if not username or not password:
                return make_response(
                    jsonify({'error': '需要认证'}),
                    401,
                    {'WWW-Authenticate': 'Basic realm="Login Required"'}
                )
            
            # 验证凭据
            if not verify_password(username, password):
                return make_response(
                    jsonify({'error': '无效的用户名或密码'}),
                    401,
                    {'WWW-Authenticate': 'Basic realm="Login Required"'}
                )
            
            # 检查角色
            user_role = get_user_roles(username)
            if user_role != required_role and required_role != "any":
                return jsonify({'error': '权限不足'}), 403
            
            request.user = {
                'username': username,
                'role': user_role
            }
            
            return f(*args, **kwargs)
        return decorated_function
    return decorator

# 公共接口 - 无需认证
@app.route('/')
def index():
    return jsonify({
        'message': '欢迎访问API',
        'endpoints': {
            '/public': '公共接口',
            '/protected': '需要认证的接口',
            '/admin': '管理员接口',
            '/profile': '用户资料',
            '/users': '用户列表（管理员）'
        }
    })

@app.route('/public')
def public_api():
    return jsonify({
        'message': '这是公共接口，无需认证',
        'timestamp': '2024-01-20T10:00:00Z'
    })

# 受保护接口 - 使用flask-httpauth
@app.route('/protected')
@auth.login_required
def protected_api():
    return jsonify({
        'message': f'你好, {auth.current_user()}! 你已成功认证',
        'role': get_user_roles(auth.current_user()),
        'access': '受保护资源'
    })

# 管理员接口 - 使用自定义装饰器
@app.route('/admin')
@role_required('admin')
def admin_api():
    return jsonify({
        'message': f'欢迎管理员: {request.user["username"]}',
        'admin_features': ['用户管理', '系统设置', '日志查看'],
        'timestamp': '2024-01-20T10:00:00Z'
    })

# 用户资料接口
@app.route('/profile')
@auth.login_required
def user_profile():
    username = auth.current_user()
    user_info = users_db.get(username, {})
    
    return jsonify({
        'username': username,
        'role': get_user_roles(username),
        'email': user_info.get('email', 'N/A'),
        'authenticated': True
    })

# 用户列表（仅管理员）
@app.route('/users')
@role_required('admin')
def list_users():
    # 不返回密码哈希
    users_info = []
    for username, info in users_db.items():
        users_info.append({
            'username': username,
            'role': info['role'],
            'email': info.get('email', 'N/A')
        })
    
    return jsonify({
        'total': len(users_info),
        'users': users_info
    })

# 创建新用户（示例）
@app.route('/users', methods=['POST'])
@role_required('admin')
def create_user():
    data = request.get_json()
    
    if not data or 'username' not in data or 'password' not in data:
        return jsonify({'error': '需要用户名和密码'}), 400
    
    username = data['username']
    password = data['password']
    role = data.get('role', 'user')
    email = data.get('email', '')
    
    if username in users_db:
        return jsonify({'error': '用户已存在'}), 400
    
    # 存储用户（生产环境使用数据库）
    users_db[username] = {
        'password_hash': generate_password_hash(password),
        'role': role,
        'email': email
    }
    
    return jsonify({
        'message': '用户创建成功',
        'username': username,
        'role': role
    }), 201

# 注销端点
@app.route('/logout')
@auth.login_required
def logout():
    # HTTP Basic Auth是无状态的，客户端只需清除凭据
    return jsonify({
        'message': '已注销，请清除浏览器保存的凭据',
        'note': 'HTTP Basic Auth是无状态的，服务器端无会话'
    })

# 健康检查
@app.route('/health')
def health_check():
    return jsonify({
        'status': 'healthy',
        'service': 'Basic Auth API',
        'timestamp': '2024-01-20T10:00:00Z'
    })

# 错误处理
@app.errorhandler(401)
def unauthorized(error):
    return make_response(
        jsonify({'error': '需要认证'}),
        401,
        {'WWW-Authenticate': 'Basic realm="Login Required"'}
    )

@app.errorhandler(403)
def forbidden(error):
    return jsonify({'error': '权限不足'}), 403

@app.errorhandler(404)
def not_found(error):
    return jsonify({'error': '资源不存在'}), 404

if __name__ == '__main__':
    port = int(os.getenv('PORT', 5000))
    debug = os.getenv('DEBUG', 'False').lower() == 'true'
    
    print(f"Basic Auth API 启动在: http://localhost:{port}")
    print(f"示例用户: admin/admin123, alice/alice456, bob/bob789")
    print(f"公共接口: http://localhost:{port}/public")
    print(f"受保护接口: http://localhost:{port}/protected")
    print(f"管理员接口: http://localhost:{port}/admin")
    
    app.run(host='0.0.0.0', port=port, debug=debug)