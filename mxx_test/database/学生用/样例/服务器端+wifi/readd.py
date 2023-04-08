import sqlite3

conn = sqlite3.connect('data.db')
cur = conn.cursor()
cur.execute('create table sensorlog(id integer primary key autoincrement,username text,sensorid integer,sensorvalue real,updatetime text)')

cur.execute('insert into sensorlog(username,sensorid,sensorvalue,updatetime) values(?,?,?,?)',
                ('xxx', 1, 600, '20230329'))
conn.commit()
cur.close()
conn.close()


  
