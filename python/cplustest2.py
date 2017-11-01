# -*- coding: utf-8 -*-
"""
Created on Tue Jun 20 11:38:26 2017

@author: 47108
"""
import qrcode
from PIL import Image

import threading

import requests


def qrmakethread(li,b,surl,fpath):
    print('this is qr make:')
    print(li)
    filepostR(surl,fpath)
    
    img=qrcode.make(li)
    imf=b+'.png'
    with open(imf,'wb')as f:
        img.save(f)
    im=Image.open(imf)
    im.show()
    
def requefinR(surl,a):#这个使用一句话就可以发送这个消息了，哈哈哈
    print("this is requefin R useinfo!")
    r=requests.get(surl+'userinfo',params=a)
    #print(r)
    return r.text
    
def filepostR(surl,fpath): #主要应该还用这个就行 multidata
    print('this is filepost :'+fpath); #files={'file':open('C:/Users/47108/Desktop/14.txt','rb')} 注意反斜杠的方向一定要对，否则不能打开文件
    files={'file':(fpath,open(fpath,'r'),'multipart/form-data',{'Expires': '0'})}
    url=surl+'upload'
    r=requests.post(url,files=files)
    print(r.text)

def fuseall(par):
    #par=['415.365','258.664','458.166','152.695','158.15979','288.4767','45.3682','475.36598','125.3652','4.3326']
    #fn=['zhuxianwei','18917192899','C:/Users/47108/Desktop/web3d/pythonweb/jhzhu.obj']

    print(par)
    fnamearry=par[22].split('/')
    fname=''
    if(len(fnamearry)>1):
        fname=fnamearry[len(fnamearry)-1]
    else:
        fname=fnamearry[0]

    print('single name :'+fname)
    #url='http://17347b39l4.imwork.net:14869/'
    url='http://192.168.0.112:3000/'
    #t2 = threading.Thread(target=filepostR,args=(url,fn[2],))
    #t2.start()
    ins={'name':par[20],'phone':par[21],'file':fname,'q1':par[0],'q2':par[1],'q3':par[2],'q4':par[3],'q5':par[4],'q6':par[5],'q7':par[6],'q8':par[7],'q9':par[8],'q10':par[9],'q11':par[10],'q12':par[11],'q13':par[12],'q14':par[13],'q15':par[14],'q6':par[15],'q17':par[16],'q18':par[17],'q19':par[18],'q20':par[19]}
    print(ins)
    
    t1 = threading.Thread(target=qrmakethread,args=(requefinR(url,ins),par[20],url,par[22]))
    t1.start()
    return 49

def test(par):
    print(par)
    for i in par :
        print(i)
        print(str(i))
    return 781
#test([4564,45464,7897])
