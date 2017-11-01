# -*- coding: utf-8 -*-
"""
Created on Tue Jun 20 11:38:26 2017

@author: 47108
"""

import http.client,urllib.parse
import qrcode
from PIL import Image

import threading

import requests

def httpconnect(a):
    httpClient = None
    #params = urllib.parse.urlencode({'@number': 12524, '@type': 'issue', '@action': 'show'})
    headers='/userinfo?name='+a[0]+'&phone='+a[1]
    
    try:
        httpClient = http.client.HTTPConnection('localhost', 3000, timeout=30)
        httpClient.request('GET', headers)
     
        #response是HTTPResponse对象
        response = httpClient.getresponse()
        #print (response.status)
        #print (response.reason)
        gwr=str(response.read())
        ct=gwr.split("'")
        gf='http://'+ct[1]
        print(gf)
        return gf
    except Exception as e:
        print (e)
        return 0
    finally:
        if httpClient:
            httpClient.close()

def qrmake(li,b):
    #hi='17319253039'
    #li='http://192.168.0.111:3000/cf/'+hi
    print(li)
    print(b)
    
    img=qrcode.make(li)
    imf=b+'.png'
    with open(imf,'wb')as f:
        img.save(f)
    im=Image.open(imf)
    im.show()


def qrmakethread(li,b):
    print(li)
    print(b)
    img=qrcode.make(li)
    imf=b+'.png'
    with open(imf,'wb')as f:
        img.save(f)
    im=Image.open(imf)
    im.show()


def hawinput():
    cont=[]
    cont.append(input("请输入您的名字："))
    cont.append(input("请输入您的手机号码："))
    cont.append(input("请输入您的obj文件路径："))
    return cont
    
 #qrmake(httpconnect(cont),cont[0]);
    
def requefin(a):#这个使用一句话就可以发送这个消息了，哈哈哈
    r=requests.get('http://192.168.0.111:3000/userinfo',a) 
    #print(r)
    return r.text
    #print(r.text)#这个是回复的信息
    
def requefinR(surl,a):#这个使用一句话就可以发送这个消息了，哈哈哈
    r=requests.get(surl+'userinfo',a) 
    #print(r)
    return r.text
    
def filepost(fpath): #主要应该还用这个就行 multidata
    print('filepost :'+fpath); #files={'file':open('C:/Users/47108/Desktop/14.txt','rb')} 注意反斜杠的方向一定要对，否则不能打开文件
    files={'file':(fpath,open(fpath,'r'),'multipart/form-data',{'Expires': '0'})}
    url='http://192.168.0.106:3000/upload'
    r=requests.post(url,files=files)
    print(r.text)
    
def filepostR(surl,fpath): #主要应该还用这个就行 multidata
    print('filepost :'+fpath); #files={'file':open('C:/Users/47108/Desktop/14.txt','rb')} 注意反斜杠的方向一定要对，否则不能打开文件
    files={'file':(fpath,open(fpath,'r'),'multipart/form-data',{'Expires': '0'})}
    url=surl+'upload'
    r=requests.post(url,files=files)
    print(r.text)

#requefin({'name':'chendong','phone':'17319253093'})

def posttest(f):
    #files={'file':open('123.obj','rb')}
    print('this is file post :'+f)
    files={'file':open(f,'rb')}
    r = requests.post("http://192.168.0.111:3000/upload", files=files)
    
    print(r.text)
    
def filemag():
    f=open('123.obj','r') #files={'file':open('C:/Users/47108/Desktop/14.txt','rb')} 注意反斜杠的方向一定要对，否则不能打开文件
    obj=f.read()
    print(len(obj))

insert={'name':'chendong3','phone':'18129235946','file':'123.obj','q1':'165.16546','q2':'165.16546','q3':'165.16546','q4':'165.16546','q5':'165.16546','q6':'165.16546','q7':'165.16546','q8':'165.16546','q9':'165.16546','q10':'165.16546'}

#requefin(insert);

def fuseall(par):
    if len(par)<10:
        return -1
    fn=hawinput()
    fnamearry=fn[2].split('/')
    fname=''
    if(len(fnamearry)>1):
        fname=fnamearry[len(fnamearry)-1]
    else:
        fname=fnamearry[0]
        print('single name'+fname)
    filepost(fn[2])
    ins={'name':fn[0],'phone':fn[1],'file':fname,'q1':par[0],'q2':par[1],'q3':par[2],'q4':par[3],'q5':par[4],'q6':par[5],'q7':par[6],'q8':par[7],'q9':par[8],'q10':par[9]}
    print(ins)
    
    t1 = threading.Thread(target=qrmakethread,args=(requefin(ins),fn[0],))
    t1.start()
    #qrmake(requefin(ins),fn[0])
    
giveout=['415.365','258.664','458.166','152.695','158.15979','288.4767','45.3682','475.36598','125.3652','4.3326']

#fuseall(giveout)

def fuseall2():
    par=['415.365','258.664','458.166','152.695','158.15979','288.4767','45.3682','475.36598','125.3652','4.3326']
    fn=['zhuxianwei','18617192899','jhzhu.obj']
    fnamearry=fn[2].split('/')
    fname=''
    if(len(fnamearry)>1):
        fname=fnamearry[len(fnamearry)-1]
    else:
        fname=fnamearry[0]
        print('single name'+fname)
    url='http://17347b39l4.imwork.net:14869/'
    t2 = threading.Thread(target=filepostR,args=(url,fn[2],))
    t2.start()
    ins={'name':fn[0],'phone':fn[1],'file':fname,'q1':par[0],'q2':par[1],'q3':par[2],'q4':par[3],'q5':par[4],'q6':par[5],'q7':par[6],'q8':par[7],'q9':par[8],'q10':par[9]}
    print(ins)
    
    t1 = threading.Thread(target=qrmakethread,args=(requefinR(url,ins),fn[0],))
    t1.start()
    return 4399

fuseall2()
#filepost('jhzhu.obj')