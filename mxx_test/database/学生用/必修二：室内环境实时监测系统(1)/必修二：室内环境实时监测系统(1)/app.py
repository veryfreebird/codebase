import sqlite3
import datetime
from flask import Flask,render_template,request
# 指定数据库位置
DATABASE = 'data/data.db'
global turn_off   # 反向控制开关变量
turn_off = 0
ip = "192.168.244.134"  # 服务器绑定本地ip的地址
port = "8080"    # 服务器绑定端口号
url = ip + ':' + port


app = Flask(__name__, static_url_path='')
@app.route('/')
def hello():
    # 链接数据库
    db = sqlite3.connect(DATABASE)
    # 获取游标
    cur = db.cursor()
    # 执行SQ语句
    cur.execute("SELECT*FROM sensorlog WHERE sensorid=1")  # select from sensorlog where sensorid=1
    # 获取所有数据
    data = cur.fetchall()
    # 关闭游标
    cur.close()
    # 关闭链接
    db.close()

    temp1 = data[len(data)-1]   # 获取列表中最新元组
    temp = temp1[2]  # 获取元组中温度数据
    light = temp1[3]
    hum = temp1[4]
    return render_template('vews.html',data=data,temp=temp,light=light,hum=hum,url=url)

@app.route("/input",methods=['POST','GET'])
def add_data():
    # http请求方式
    if request.method == 'POST':
        # 从request中取出id
        sensorid = int(request.form.get('id'))
        # 从request中取出val值
        tempvalue = float(request.args.get('tempval'))
        lightvalue = float(request.args.get('lightval'))
        humvalue = float(request.args.get('humval'))
    else:
        sensorid = int(request.args.get('id'))
        tempvalue = float(request.args.get('tempval'))
        lightvalue = float(request.args.get('lightval'))
        humvalue = float(request.args.get('humval'))

    # 获取本地系统时间
    nowtime = datetime.datetime.now()
    # 格式化系统时间
    nowtime = nowtime.strftime('%Y-%m-%d %H:%M:%S')
    print(nowtime)
    db = sqlite3.connect(DATABASE)
    cur = db.cursor()
    # insert into sensorlog()value()
    cur.execute('''INSERT INTO sensorlog(sensorid,tempvalue,lightvalue,humvalue,updatetime)VALUES(%d,%f,%f,%f,'%s')''' %(sensorid,tempvalue,lightvalue,humvalue,nowtime))
    # 提交事务
    db.commit()
    # select * from sensorlist where sensorid
    cur.execute("SELECT*FROM sensorlist where sensorid = %d" %sensorid)
    rv = cur.fetchall()
    cur.close()
    db.close()
    maxrv = rv[0][2]
    minrv = rv[0][3]
    if tempvalue > maxrv or tempvalue<minrv:
        return '0'
    else:
        return '1'


@app.route("/turn_off_light",methods=['POST','GET'])
def turn_light():
    global turn_off
    if request.method == 'GET':
        print("要开灯啦")
        turn_off = 1
    else:
        print('要关灯啦')
        turn_off =0
    return '200'


@app.route("/inputs",methods=['POST','GET'])
def control_light():
    if turn_off == 1:
        return 'turn'
    else:
        return 'off'


@app.route("/download",methods=['POST','GET'])
def sensordata_Download():
    print("正在下载历史数据。。。")
    # 链接数据库
    db = sqlite3.connect(DATABASE)
    cur = db.cursor()
    cur.execute("SELECT*FROM sensorlog WHERE sensorid=1")  # select from sensorlog where sensorid=1
    data = cur.fetchall()
    f = open("data/室内环境检测系统历史数据.txt",'w')
    f.write("记录编号"+'\t'+"温度"+'\t'+"湿度"+'\t'+"亮度"+'\t'+"记录时间"+"\r\n")
    for i in data:
            f.write('  '+str(i[0])+'\t'+str(i[2])+'\t'+str(i[3])+'\t'+str(i[4])+'\t'+str(i[5])+"\r\n")
    f.close()
    return '200'



if __name__ == '__main__':
    app.run(host=ip, port=port, debug=True, use_reloader=False)
