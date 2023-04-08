# 1.导入sqlite3模块
import sqlite3

# 2.链接数据库 connect
db = sqlite3.connect('data/data.db')  # 可以指定数据库路径,如果数据库不存在，则创建一个新的数据库进行链接
print(db)

# 3.创建游标对象
cur = db.cursor()

# 4.编写创建表
sensorlist_sql = '''create table sensorlist(sensorid integer  primary key,  
                                 sensorname varchar(50),
                                 maxvalue integer,
                                 minvalue integer)'''

sensorlog_sql = '''create table sensorlog(logid integer primary key,
                                          sensorid integer,
                                          tempvalue float,
                                          lightvalue float,
                                          humvalue float,
                                          updatetime time)'''

insert_sensor_sql = "insert into sensorlist(sensorid,sensorname,maxvalue,minvalue)values(?,?,?,?)"

try:
    # 5.执行sql语句
    cur.execute(sensorlist_sql)
    cur.execute(sensorlog_sql)
    print("创建表成功")
    cur.execute(insert_sensor_sql,(1,"温度传感器",30,10))
    db.commit()
    print("数据插入成功")


except Exception as erro:
    print(erro)
    print("创建表失败")
    db.rollback()
    print("数据插入失败")

finally:
    # 6.关闭游标
    cur.close()
    # 7.关闭链接
    db.close()