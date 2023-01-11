from flask import Flask,render_template,request,url_for,flash,redirect,jsonify
import sqlite3
import os
DATABASE = 'data.db'
import numpy as np
import cv2
def mlsb(path):
    b=0.01535592
    m = np.loadtxt("test.txt")
    def sigmoid(z):
        s = 1 / (1 + np.exp(-z))
        return s 
    image=cv2.imread(path)
    image=cv2.resize(image,(64,64))
    # my_image = skimage.transform.resize(image, output_shape=(num_px,num_px)).reshape((1, num_px*num_px*3)).T
    data=np.asarray(image)
    data=data.reshape(64*64*3,1)
    A = sigmoid(np.dot(m,data) + b)
    print(A[0])
    if(A[0]!=1.0):
        print("cat2.jpg是猫咪")
        return 1
    else:
         return 0

def connect_db():
    conn=sqlite3.connect('data.db')
    conn.row_factory=sqlite3.Row
    return conn
app=Flask(__name__)
@app.route("/users/<user_id>", methods=["GET"])
def get_user(user_id):
    """获取某个用户信息"""
 
    conn = connect_db()
                
    print(user_id)               
    conn.execute("INSERT INTO tems (dat) VALUES (?)",(user_id,))

    conn.commit()
    conn.close()
    print((user_id)) 
    return (user_id)

@app.route("/250")
def index():
 conn=connect_db()
 s=conn.execute('select * from led').fetchall()
 conn.close()
 print(s[0]['key'])
 return render_template('1.html',s=s[0]['key'])
#  return jsonify(s[0]['key']) 
@app.route('/esp8266', methods=('GET', 'POST'))
def new():
    if request.method == 'POST':
        title = request.form['title']
        content = str((-int(title)+1))

        if not title:
            return('标题不能为空!')
        
        else:
            conn = connect_db()
            conn.execute('DELETE FROM led WHERE key>=0')
                  
            conn.execute('INSERT INTO led (key) VALUES (?)',
                         (title))
            conn.execute('INSERT INTO led (key) VALUES (?)',
                         (content))
            conn.commit()
            conn.close()
    return render_template('new.html') 
@app.route("/dat")
def dat():
    n=0;
    conn=connect_db()
    s=conn.execute('select * from tems').fetchall()
    conn.close()
    s.reverse()
    for dat in s:
        n=n+int(dat['dat'])
    n=n/len(s)
    return render_template('6.html',s=s,n=n)
@app.route('/up')
def up():
    return render_template('shibei.html')
@app.route('/up_photo', methods=['post'])
def up_photo():
    
        img = request.files['photo']
        print(img)
        print(666)
       
        img.save(basedir+'\\static\\1.jpg')
        print(basedir+'1.jepg')
        if(mlsb(basedir+'\\static\\1.jpg')==1):
            s=1
        else:
            s= 0
        return render_template('shibei.html',s=s)



if __name__=='__main__':
    app.debug=True
    app.run('0.0.0.0')