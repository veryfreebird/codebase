from flask import Flask, request, render_template
from flask_bootstrap import Bootstrap           # 导入网页模板工具模块
import datetime
import sqlite3

app = Flask(__name__)
bootstrap = Bootstrap(app)


@app.route('/', methods=['GET'])
def index():
    conn = sqlite3.connect('data.db')
    cur = conn.cursor()
    cur.execute('select * from sensorlog where sensorid=1')
    data = cur.fetchall()
    cur.close()
    conn.close()
    return render_template('index.html', data=data)

@app.route('/input', methods=['GET'])
def insert():
    id = int(request.args.get('id'))
    username = request.args.get('user')
    value = float(request.args.get('val'))
    print(id,username,value)
    nowtime = datetime.datetime.now()
    nowtime = nowtime.strftime('%Y-%m-%d %H:%M:%S')
    conn = sqlite3.connect('data.db')
    cur = conn.cursor()
    cur.execute('insert into sensorlog(username,sensorid,sensorvalue,updatetime) values(?,?,?,?)',
                (username, id, value, nowtime))
    conn.commit()
    cur.close()
    conn.close()
    if value > 500:
        return '0'
    else:
        return '1'

@app.route('/set', methods=['GET'])
def set_light():
    return '等待你的完善'

@app.route('/view', methods=['GET'])
def view():
    return '等你完善'

if __name__ == '__main__':
    app.run(host='0.0.0.0', port=8000, debug=True)
