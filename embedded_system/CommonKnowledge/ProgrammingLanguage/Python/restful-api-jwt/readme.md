# 0.目录结构
```
restful-api-jwt/
├── app.py              # 主应用文件
├── config.py           # 配置文件
├── requirements.txt    # 依赖包
├── ssl/               # SSL证书目录
│   ├── server.crt
│   └── server.key
└── README.md
```

# 1. 生成SSL证书
## 创建SSL目录
mkdir ssl
cd ssl
## 生成私钥和自签名证书（开发环境使用）
openssl req -x509 -newkey rsa:4096 -nodes \
  -out server.crt -keyout server.key \
  -days 365 -subj "/C=CN/ST=Beijing/L=Beijing/O=Dev/CN=localhost"

# 2. 设置环境变量
## .env
SECRET_KEY=your-super-secret-key-change-in-production
JWT_SECRET_KEY=jwt-super-secret-key-change-in-production
DEBUG=True

# 3. 运行应用
## 安装依赖
pip install -r requirements.txt

## 运行应用
python app.py

# 4. 测试API
## 用户登录：
curl -k -X POST https://localhost:5000/auth/login \
  -H "Content-Type: application/json" \
  -d '{"username": "admin", "password": "admin123"}'

## 获取项目列表：
curl -k https://localhost:5000/api/items \
  -H "Authorization: Bearer YOUR_ACCESS_TOKEN"

## 创建项目：
curl -k -X POST https://localhost:5000/api/items \
  -H "Authorization: Bearer YOUR_ACCESS_TOKEN" \
  -H "Content-Type: application/json" \
  -d '{"name": "测试项目", "description": "这是一个测试项目"}'

## 刷新Token：
curl -k -X POST https://localhost:5000/auth/refresh \
  -H "Authorization: Bearer YOUR_REFRESH_TOKEN"

