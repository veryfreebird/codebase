from flask import Flask, request, render_template
from flask_bootstrap import Bootstrap           # 导入网页模板工具模块
import datetime
import sqlite3

import serial
app = Flask(__name__)
bootstrap = Bootstrap(app)

@app.route('/', methods=['GET'])
def index():
    #串口代码
    ser=serial.Serial()
    ser.baudrate=115200
    ser.port='COM3'
    ser.open()
    ser.write("on".encode())
    data=ser.readline().strip().decode().split()
    print(data)
    nowtime = datetime.datetime.now()
    nowtime = nowtime.strftime('%Y-%m-%d %H:%M:%S')
    username=data[0]
    id=int(data[1])
    value=float(data[2])
    if value>500:
        ser.write("2".encode())
    else:
        ser.write("1".encode())
    conn = sqlite3.connect('data.db')
    cur = conn.cursor()
    cur.execute('insert into sensorlog(username,sensorid,sensorvalue,updatetime) values(?,?,?,?)',
                (username, id, value, nowtime))
    conn.commit()
    cur.execute('select * from sensorlog where sensorid=1')
    data = cur.fetchall()
    cur.close()
    conn.close()
    
    return render_template('index.html', data=data)
@app.route('/view', methods=['GET'])
def view():
    return '等你完善'

if __name__ == '__main__':
    app.run(host='0.0.0.0', port=8000, debug=True)
