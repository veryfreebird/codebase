# config.py
import os
from datetime import timedelta
from dotenv import load_dotenv

load_dotenv()

class Config:
    # 基础配置
    SECRET_KEY = os.getenv('SECRET_KEY', 'your-secret-key-change-in-production')
    DEBUG = os.getenv('DEBUG', 'False').lower() == 'true'
    
    # JWT配置
    JWT_SECRET_KEY = os.getenv('JWT_SECRET_KEY', 'jwt-secret-key-change-me')
    JWT_ACCESS_TOKEN_EXPIRES = timedelta(minutes=15)
    JWT_REFRESH_TOKEN_EXPIRES = timedelta(days=7)
    JWT_ALGORITHM = 'HS256'
    
    # SSL配置
    SSL_CERT = 'ssl/server.crt'
    SSL_KEY = 'ssl/server.key'
    
    # 用户数据库（实际项目中使用真实数据库）
    USERS = {
        'admin': {
            'password': 'admin123',  # 生产环境使用哈希密码
            'role': 'admin',
            'user_id': 1
        },
        'user': {
            'password': 'user123',
            'role': 'user',
            'user_id': 2
        }
    }