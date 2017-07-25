import math
import numpy as np
import operator
import pyprind
import pandas as pd
import re
from nltk.corpus import stopwords
import pyprind

dicpos = {}
dicneg = {}
hashp = {}
cntpos = 0
cntneg = 0
vect_dicpos = []
vect_dicneg = []
vect_tfpos = []
vect_tfneg = []
vect_tfidfpos = []
vect_tfidfneg = []

# func:
def preprocess(text, polars):
    stopword = stopwords.words('english')
    for i in range(len(text)):
        lines = text[i]
        polar = polars[i]
        lines = lines.strip()
        lines = re.sub(r'[\W]+', ' ', lines.lower())
        tmp = [word for word in lines.split() if not (word in stopword)]
        # print(tmp)
        hashing(tmp[1:], polar)
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
        tmp = list(set(tmp))
        if polar == 1:
            vect_dicpos.append(tmp)
        else:
            vect_dicneg.append(tmp)


def hashing(lis, polar):
    for word in lis:
        if polar == 1:
            if word in dicpos:
                dicpos[word] += 1
            else:
                dicpos[word] = 1
        else:
            if word in dicneg:
                dicneg[word] += 1
            else:
                dicneg[word] = 1


def generate_idf(n):
    cnt = 0
    for element in dicpos:
        cnt = dicpos[element]
        if element in dicneg:
            cnt += dicneg[element]
        hashp[element] = math.log((1 + n) * 1.0 / (1 + cnt))


def generate_tfidf():
    for i in range(len(vect_dicneg)):
        lis = vect_dicneg[i]
        tmp = {}
        for word in lis:
            try:
                tmp[word] = ((hashp[word] + 1.0) * (1.0 + vect_tfneg[i][word]))
            except:
                continue
        vect_tfidfneg.append(tmp)
    for i in range(len(vect_dicpos)):
        lis = vect_dicpos[i]
        tmp = {}
        for word in lis:
            try:
                tmp[word] = ((hashp[word] + 1.0) * (1.0 + vect_tfpos[i][word]))
            except:
                continue
        vect_tfidfpos.append(tmp)
    return vect_tfidfneg, vect_tfidfpos

def generate_rateX(X):
    dicX = {}
    lnnX = len(X)
    for word in X:
        if word in dicX:
            dicX[word] += 1.0 / lnnX
        else:
            dicX[word] = 1.0 / lnnX
    for ele in dicX:
        try:
            dicX[ele] = (dicX[ele] + 1.0) * (hashp[ele] + 1.0)
        except:
            dicX[ele] = (dicX[ele] + 1.0)
    return dicX


def knn(X, f, K=10):
    diffneg = []
    diffpos = []
    dicX = {}
    dicX = generate_rateX(X)
    for ii in range(len(vect_dicpos)):
        lis = vect_dicpos[ii]
        diff = 0
        XX = list(set(X))
        liss = list(set(lis))
        markXX = np.zeros(len(XX))
        markliss=np.zeros(len(liss))
        for i in range(len(liss)):
            for j in range(len(XX)):
                if liss[i] == XX[j]:
                    try:
                        diff += (dicX[XX[j]] - vect_tfidfpos[ii][XX[j]])**2
                    except:
                        diff += 0.4
                    markliss[i] = 1
                    markXX[j] = 1
                    break
        for i in range(len(XX)):
            if markXX[i] == 0:
                try:
                    diff += (dicX[XX[i]])**2
                except:
                    diff +=1.0
        for i in range(len(liss)):
            if markliss[i] == 0:
                try:
                    diff += (vect_tfidfpos[ii][liss[i]])**2
                except:
                    diff +=1.0
        diffpos.append(diff * 1.0)

    for ii in range(len(vect_dicneg)):
        lis = vect_dicneg[ii]
        diff = 0
        liss = list(set(lis))
        XX = list(set(X))
        markliss = np.zeros(len(liss))
        markXX = np.zeros(len(XX))
        for i in range(len(liss)):
            for j in range(len(XX)):
                if liss[i] == XX[j]:
                    try:
                        diff += (dicX[XX[j]] - vect_tfidfneg[ii][XX[j]])**2
                    except:
                        diff += 0.7
                    markXX[j] = 1
                    markliss[i] = 1
                    break
        for i in range(len(XX)):
            if markXX[i] == 0:
                try:
                    diff += (dicX[XX[i]])**2
                except:
                    diff += 1.0
        for i in range(len(liss)):
            if markliss[i] == 0:
                try:
                    diff += (vect_tfidfpneg[ii][liss[i]])**2
                except:
                    diff += 1.0
        diffneg.append(diff * 1.0)

    diffpos.sort(reverse=True)
    diffneg.sort(reverse=True)
    posp = 0
    posn = 0
    ans = []
    while (True):
        if diffpos[posp] < diffneg[posn]:
            ans.append([diffpos[posp], 1])
            posp += 1
        else:
            ans.append([diffneg[posn], -1])
            posn += 1
        if posp + posn == K:
            break
    for lines in ans:
        f.write(str(lines))
    f.write("\n predict: ")
    ann = 0
    if posp > posn:
        f.write(str(1.0))
        ann = 1.0
    else:
        f.write(str(-1.0))
        ann = -1.0
    f.write("\n")
    return ans, ann


def check(text, label, f):
    pbar = pyprind.ProgBar(100)
    stopword = stopwords.words('english')
    cntcor = 0
    cnttot = 0
    for i in range(len(text)):
        lines = text[i].strip()
        lines = re.sub(r'[\W]+', ' ', lines.lower())
        tmp = [word for word in lines.split() if word not in stopword]
        ans, ann = knn(tmp, f, K=5)
        if (ann == 1) & (label[i] == 1):
            cntcor += 1
        if (ann == -1) & (label[i] == 0):
            cntcor += 1
        cnttot += 1
        pbar.update()
    print("\n\n\n final correct rate:")
    print(str(cntcor * 1.0 / cnttot))


# local space

f = open('D://data//movie_data.csv')
df = pd.DataFrame()
cnt = 0
text = []
for line in f:
    try:
        text.append([str(line[:-6]), int(line[-5])])
    except:
        pass

txt = []
lab = []
for line, label in text:
    txt.append(line)
    lab.append(label)

preprocess(txt[:800], lab[:800])

generate_idf(800)
generate_tfidf()
f = open('ans', 'w')
check(txt[800:900], lab[800:900], f)

'''
cor rate:
base = 800
cor = 0.62
base = 500
cor = 0.53
'''
