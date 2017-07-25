import math
import numpy as np
import operator
import pyprind
import pandas as pd
import re
from nltk.corpus import stopwords

vect_tfpos = []
vect_tfneg = []

def preprocess(text, polars):
    stopword = stopwords.words('english')
    for i in range(len(text)):
        lines = text[i]
        polar = polars[i]
        lines = lines.strip()
        lines = re.sub(r'[\W]+', ' ', lines.lower())
        tmp = [word for word in lines.split() if not (word in stopword)]
        # print(tmp)
        tmpdic = {}
        lenn = len(tmp)
        for word in tmp:
            if word in tmpdic:
                tmpdic[word] += 1.0 / lenn * 1.0
            else:
                tmpdic[word] = 1.0 / lenn * 1.0
        if polar == 1:
            vect_tfpos.append(tmpdic)
        else:
            vect_tfneg.append(tmpdic)

def knn(X, K=10):
    simneg = []
    simpos = []
    ww={}
    for word in X:
        if not(word in ww):
            ww[word] = 1.0/len(X)
        else:
            ww[word] += 1.0/len(X)
    for i in range(len(vect_tfpos)):
        dic = vect_tfpos[i]
        sim = 0.0
        sqrr = 0.0
        for word in ww:
            if word in dic:
                sim += ww[word]*dic[word]
                sqrr += dic[word]**2
            else:
                sim += -ww[word]
                sqrr += 1.0
        sim = sim/sqrr
        simpos.append(sim)
    for i in range(len(vect_tfneg)):
        dic = vect_tfneg[i]
        sim = 0.0
        sqrr = 0.0
        for word in X:
            if word in dic:
                sim += 1.0*dic[word]
            else:
                sim += 0.0
                sqrr += 1.0
        sim = sim/sqrr
        simneg.append(sim)
    simneg.sort(reverse=True)
    simpos.sort(reverse=True)
    cnt = 0
    ans = []
    posp = 0
    posn = 0
    cntp = 0
    cntn = 0
    while(True):
        cnt += 1
        if simpos[posp] >= simneg[posn]:
            cntp += 1
            posp += 1
            ans.append([simpos[posp], 1])
        else:
            cntn += 1
            posn += 1
            ans.append([simneg[posn], -1])
        if cnt == K:
            break
    if cntp >= cntn:
        ann = 1
    else:
        ann = -1
    return ans, ann

def check(text, label, f):
    totrun = 0
    totcor = 0
    for i in range(len(text)):
        l = label[i]
        txt = text[i]
        ans, ann = knn(txt, K=7)
        for line in ans:
            f.write(str(line))
        f.write(str(ann))
        if ann==1:
            f.write(str(i)+" predict: "+str(ann)+" ori: "+str(l))
            if l == ann:
                totcor += 1
            totrun += 1
        else:
            f.write(str(i)+" predict: "+str(ann)+" ori: "+str(l))
            if l == 0:
                totcor += 1
            totrun += 1
    print("total correct: "+str(float(totcor/totrun)))

'''
base = 800
cor = 0.45
'''
