# app.py
import jwt
import ssl
from datetime import datetime, timedelta
from functools import wraps
from flask import Flask, request, jsonify, make_response
from flask_restx import Api, Resource, fields, Namespace
from werkzeug.security import generate_password_hash, check_password_hash
from config import Config

# 初始化Flask应用
app = Flask(__name__)
app.config.from_object(Config)

# 初始化API
api = Api(
    app,
    version='1.0',
    title='Secure RESTful API',
    description='使用HTTPS和JWT鉴权的RESTful API示例',
    doc='/docs',  # Swagger文档地址
    authorizations={
        'Bearer': {
            'type': 'apiKey',
            'in': 'header',
            'name': 'Authorization',
            'description': '输入: Bearer {token}'
        }
    },
    security='Bearer'
)

# 定义命名空间
auth_ns = Namespace('auth', description='认证相关操作')
api_ns = Namespace('api', description='API操作')

# 数据模型
login_model = api.model('Login', {
    'username': fields.String(required=True, description='用户名'),
    'password': fields.String(required=True, description='密码')
})

user_model = api.model('User', {
    'id': fields.Integer(readonly=True, description='用户ID'),
    'username': fields.String(required=True, description='用户名'),
    'role': fields.String(description='角色')
})

item_model = api.model('Item', {
    'id': fields.Integer(readonly=True, description='项目ID'),
    'name': fields.String(required=True, description='项目名称'),
    'description': fields.String(description='描述'),
    'created_at': fields.DateTime(readonly=True, description='创建时间')
})

# 模拟数据库
items_db = []
user_counter = 3

# JWT工具函数
def generate_token(user_id, username, role, token_type='access'):
    """生成JWT Token"""
    expires_delta = (
        Config.JWT_ACCESS_TOKEN_EXPIRES 
        if token_type == 'access' 
        else Config.JWT_REFRESH_TOKEN_EXPIRES
    )
    
    payload = {
        'user_id': user_id,
        'username': username,
        'role': role,
        'type': token_type,
        'exp': datetime.utcnow() + expires_delta,
        'iat': datetime.utcnow()
    }
    
    token = jwt.encode(
        payload, 
        Config.JWT_SECRET_KEY, 
        algorithm=Config.JWT_ALGORITHM
    )
    return token

def decode_token(token):
    """解码并验证JWT Token"""
    try:
        payload = jwt.decode(
            token, 
            Config.JWT_SECRET_KEY, 
            algorithms=[Config.JWT_ALGORITHM]
        )
        return payload
    except jwt.ExpiredSignatureError:
        return None, 'Token已过期'
    except jwt.InvalidTokenError:
        return None, '无效的Token'

# 装饰器：Token验证
def token_required(roles=None):
    def decorator(f):
        @wraps(f)
        def decorated(*args, **kwargs):
            auth_header = request.headers.get('Authorization')
            
            if not auth_header or not auth_header.startswith('Bearer '):
                return {'message': '缺少或无效的Authorization头'}, 401
            
            token = auth_header.split(' ')[1]
            payload = decode_token(token)
            
            if not payload or payload.get('type') != 'access':
                return {'message': '无效或过期的Token'}, 401
            
            # 检查角色权限
            if roles and payload.get('role') not in roles:
                return {'message': '权限不足'}, 403
            
            request.user = payload
            return f(*args, **kwargs)
        return decorated
    return decorator

# 认证相关接口
@auth_ns.route('/login')
class Login(Resource):
    @auth_ns.expect(login_model)
    def post(self):
        """用户登录，获取Token"""
        data = request.get_json()
        username = data.get('username')
        password = data.get('password')
        
        if not username or not password:
            return {'message': '用户名和密码不能为空'}, 400
        
        user = Config.USERS.get(username)
        
        if not user or user['password'] != password:
            return {'message': '用户名或密码错误'}, 401
        
        # 生成Token
        access_token = generate_token(
            user['user_id'], 
            username, 
            user['role'], 
            'access'
        )
        
        refresh_token = generate_token(
            user['user_id'], 
            username, 
            user['role'], 
            'refresh'
        )
        
        return {
            'message': '登录成功',
            'access_token': access_token,
            'refresh_token': refresh_token,
            'expires_in': Config.JWT_ACCESS_TOKEN_EXPIRES.total_seconds(),
            'user': {
                'id': user['user_id'],
                'username': username,
                'role': user['role']
            }
        }, 200

@auth_ns.route('/refresh')
class RefreshToken(Resource):
    def post(self):
        """刷新Access Token"""
        auth_header = request.headers.get('Authorization')
        
        if not auth_header or not auth_header.startswith('Bearer '):
            return {'message': '缺少或无效的Authorization头'}, 401
        
        refresh_token = auth_header.split(' ')[1]
        payload = decode_token(refresh_token)
        
        if not payload or payload.get('type') != 'refresh':
            return {'message': '无效的Refresh Token'}, 401
        
        # 生成新的Access Token
        new_access_token = generate_token(
            payload['user_id'],
            payload['username'],
            payload['role'],
            'access'
        )
        
        return {
            'access_token': new_access_token,
            'expires_in': Config.JWT_ACCESS_TOKEN_EXPIRES.total_seconds()
        }, 200

# 受保护的API接口
@api_ns.route('/items')
class ItemList(Resource):
    @api_ns.doc(security='Bearer')
    @token_required()
    def get(self):
        """获取所有项目（需要登录）"""
        return {'items': items_db}, 200
    
    @api_ns.expect(item_model)
    @api_ns.doc(security='Bearer')
    @token_required(['admin'])
    def post(self):
        """创建新项目（需要管理员权限）"""
        data = request.get_json()
        
        if not data.get('name'):
            return {'message': '项目名称不能为空'}, 400
        
        new_item = {
            'id': len(items_db) + 1,
            'name': data['name'],
            'description': data.get('description', ''),
            'created_at': datetime.utcnow().isoformat()
        }
        
        items_db.append(new_item)
        return {'item': new_item, 'message': '创建成功'}, 201

@api_ns.route('/items/<int:item_id>')
class Item(Resource):
    @api_ns.doc(security='Bearer')
    @token_required()
    def get(self, item_id):
        """获取指定项目"""
        item = next((i for i in items_db if i['id'] == item_id), None)
        if not item:
            return {'message': '项目不存在'}, 404
        return {'item': item}, 200
    
    @api_ns.expect(item_model)
    @api_ns.doc(security='Bearer')
    @token_required(['admin'])
    def put(self, item_id):
        """更新项目（需要管理员权限）"""
        item = next((i for i in items_db if i['id'] == item_id), None)
        if not item:
            return {'message': '项目不存在'}, 404
        
        data = request.get_json()
        item.update({
            'name': data.get('name', item['name']),
            'description': data.get('description', item['description'])
        })
        
        return {'item': item, 'message': '更新成功'}, 200
    
    @api_ns.doc(security='Bearer')
    @token_required(['admin'])
    def delete(self, item_id):
        """删除项目（需要管理员权限）"""
        global items_db
        items_db = [i for i in items_db if i['id'] != item_id]
        return {'message': '删除成功'}, 200

@api_ns.route('/profile')
class UserProfile(Resource):
    @api_ns.doc(security='Bearer')
    @token_required()
    def get(self):
        """获取当前用户信息"""
        return {
            'user': {
                'id': request.user['user_id'],
                'username': request.user['username'],
                'role': request.user['role']
            }
        }, 200

# 注册命名空间
api.add_namespace(auth_ns, path='/auth')
api.add_namespace(api_ns, path='/api')

# 健康检查接口
@app.route('/health', methods=['GET'])
def health_check():
    return {'status': 'healthy', 'timestamp': datetime.utcnow().isoformat()}, 200

# 错误处理
@app.errorhandler(404)
def not_found(error):
    return {'message': '资源不存在'}, 404

@app.errorhandler(500)
def internal_error(error):
    return {'message': '服务器内部错误'}, 500

if __name__ == '__main__':
    # 启动HTTPS服务
    context = ssl.SSLContext(ssl.PROTOCOL_TLS)
    context.load_cert_chain(Config.SSL_CERT, Config.SSL_KEY)
    
    print(f"服务器启动在: https://localhost:5000")
    print(f"API文档地址: https://localhost:5000/docs")
    print(f"健康检查: https://localhost:5000/health")
    
    app.run(
        host='0.0.0.0',
        port=5000,
        debug=Config.DEBUG,
        ssl_context=context
    )