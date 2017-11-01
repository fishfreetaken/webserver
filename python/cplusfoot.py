# -*- coding: utf-8 -*-
"""
Created on Tue Jun 20 11:38:26 2017

@author: 47108
"""
import qrcode
from PIL import Image

import threading

import requests

def qrmakethread(a,b):
    print('this is qr make:')
    #filepostR(surl,fpath)
    urls='http://localhost/nodeup/userinfo'
    mfc='http://192.168.0.116/foot.html?user='+requefinR(urls,a)
    print(mfc)
    print(b)
    img=qrcode.make(mfc)
    imf=b+'.png'
    with open(imf,'wb')as f:
        img.save(f)
    im=Image.open(imf)
    im.show()
    
def requefinR(surl,a):
    print("this is requefin R useinfo!")
    r=requests.get(surl,params=a)
    #print(r)
    print(r.text)
    return r.text
    
def fuseall(par):
    #print(par)

    #url='http://17347b39l4.imwork.net:14869/'
    #url='http://192.168.0.112:3000/'
    

    ins={'name':par[20],'phone':par[21],'sex':par[22],'q1':par[0],'q2':par[1],'q3':par[2],'q4':par[3],'q5':par[4],'q6':par[5],'q7':par[6],'q8':par[7],'q9':par[8],'q10':par[9],'q11':par[10],'q12':par[11],'q13':par[12],'q14':par[13],'q15':par[14],'q16':par[15],'q17':par[16],'q18':par[17],'q19':par[18],'q20':par[19]}

    qrmakethread(ins,par[20])
    #t1 = threading.Thread(target=qrmakethread,args=(ins,par[20]))
    #t1.start()
    return 49

'''
t1 = threading.Thread(target=qrmakethread,args=('kfuufu','154'))
t1.start()
'''

'''
inputpara= [ 25.315,52.661,156.126,126.156,26.115,184.15,12.364,789.165,454.265,488.165,25.315,52.661,156.126,126.156,26.115,184.15,12.364,789.165,454.265,488.165,"chendong","17319263039","1"]
fuseall(inputpara)
'''
