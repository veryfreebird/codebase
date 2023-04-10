#重要的事情说三遍：我不会写！我不会写!我不会写!要是bug太多你就重写一个吧ORZ
import sqlite3
from flask import Flask,render_template,redirect,request
from flask_wtf import FlaskForm
from wtforms import SubmitField,StringField
from flask_bootstrap import Bootstrap
import sqlite3
conn = sqlite3.connect('user.db')  # user.db里默认金额300
cur = conn.cursor()
def find(cur,name,password):
    sql=('select from stuinfo where name=' + name + 'and password=' + password)
    cur.execute(sql)
    ans=cur.fetchall()
    return len(ans)!=0

class fform(FlaskForm):
    usn=StringField("username")
    psw=StringField("password")
    su=SubmitField('提交')
a="aaa"    
app=Flask(__name__)
bootstrap=Bootstrap(app)
app.config['SECRET_KEY']="hello python"
#/log   GET
@app.route('/log',methods=["GET","POST"])
def lo():
    global un,liuyan
    un=request.args.get("username")
    pw=request.args.get('password')
    print(un,pw)
'''
    if find(cur,un,pw):
        return redirect('/play')
    else:
        sql=('insert into stuinfo(username,password,money)values(' + un +',' +pw+')')#*****几个引号来着。。？不会写了QAQ
        cur.execute(sql)
        conn.commit()
        return redirect('/play')
    return render_template('logi.html',m=un)
'''
    
    #/chat  POST
@app.route('/play',methods=["GET","POST"])


#快速表单示例
@app.route('/reg',methods=['GET','POST'])
def q():
    ff=fform()
    if ff.validate_on_submit():
        global a
        a=ff.usn.data
        b=ff.psw.data
        ###if a not in userinfo:#前面写过了这里怎么改？？？
        ###    userinfo[a]=b
        ###    print(userinfo)
        return redirect("/log")
    return render_template("qform.html",form1=ff)
if __name__ =="__main__":
    app.run(host='127.0.0.1',port=8080,debug=True)

