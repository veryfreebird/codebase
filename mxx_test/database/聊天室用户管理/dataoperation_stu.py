# 1.导入sqlite3模块
import sqlite3
# 2.链接数据库 connect
def create():
    db = sqlite3.connect('user.db')  # 可以指定数据库路径,如果数据库不存在，则创建一个新的数据库进行链接
    print(db)
    # 3.创建游标对象
    cur = db.cursor()
    # 4.编写创建表
    sql = '''create table namedata( 
                                   "id" INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT,
                                    name varchar(50) ,  
                                    tall int,
                                    bmi int
                                    )'''
    try:
        # 5.执行sql语句
        cur.execute(sql)
        print("创建表成功")
    except Exception as error:
        print(error)
        print("创建表失败")
    finally:
        # 6.关闭游标
        cur.close()
        # 7.关闭链接
        db.close()
def seek(username):
    # 链接数据库
    db = sqlite3.connect(DATABASE)
    # 获取游标
    cur = db.cursor()
    # 执行SQ语句
    cur.execute("SELECT*FROM namedata WHERE name=?",[username])  
    # 获取所有数据
    data = cur.fetchall() #注意
    # 关闭游标
    cur.close()
    # 关闭链接
    db.close()
    return data
def add(data):
    db = sqlite3.connect(DATABASE)
    cur = db.cursor()
    insert_student_sql = "insert into namedata(name,tall,bmi)values(?,?,?)"
    try:
        cur.execute(insert_student_sql,(data[0],data[1],data[2]))
        db.commit() #注意
        print("数据插入成功")
    except Exception as error:
        print(error)
        db.rollback()
        print("数据插入失败")
    finally:
        # 6.关闭游标
        cur.close()
        # 7.关闭链接
        db.close()
def change(data):
    # 链接数据库
    db = sqlite3.connect(DATABASE)
    # 获取游标
    cur = db.cursor()
    # 执行SQ语句
    cur.execute("UPDATE namedata SET bmi = ? WHERE name = ?",[data[2],data[0]])  
    # 关闭游标
    cur.close()
    db.commit()
    # 关闭链接
    db.close()
def delete(name):
    # 链接数据库
    db = sqlite3.connect(DATABASE)
    # 获取游标
    cur = db.cursor()
    # 执行SQ语句
    cur.execute('delete from namedata where name= ?',[name])  
    # 关闭游标
    cur.close()
    db.commit()
    # 关闭链接
    db.close()
#创建数据库“0108A1.db”，创建数据表namedata设置字段为姓名、年龄、BMI
DATABASE = '0317A.db'
a=int(input("是否创建数据库:(1表示是，0表示否)"))
if a==1:
    create()
data=[["张三",20,22.1],["李四",18,26.1],["王五",34,18.3],["麻二",6,55]]
#插入data中的记录
for i in data:
    add(i)
#更新麻二的BMI记录为20.8
'''change(["麻二",6,20.8])
#查找王五的基本信息
print(seek("王五"))
#删除张三的数据
delete("张三")'''