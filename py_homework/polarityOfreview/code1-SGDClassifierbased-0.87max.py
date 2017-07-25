import numpy as np
from nltk.corpus import stopwords
from sklearn.feature_extraction.text import HashingVectorizer
import pandas as pd
import cmath
import os
import re
import pyprind

class SGDClassifier(object):
    def __init__(self, random_state=None, eta=0.01, shuffle=True, n_iter=10):
        self.eta = eta
        self.w_initialized = False
        self.shuffle = shuffle
        self.n_iter = n_iter
        if random_state:
            np.random.seed(random_state)

    def initialized_weights(self, m):
        self.w_ = np.zeros(1 + m)
        self.w_initialized = True

    def activation(self, X):
        return self.input(X)

    def perdict(self, X):
        output = self.activation(X)
        return np.where(output >= 0.0, 1, 0)

    def _shuffle(self, X, y):
        r = np.random.permutation(len(y))
        return X[r], y[r]

    def input(self, X):
        return np.dot(X, self.w_[1:]) + self.w_[0]

    def updateweight(self, xi, tar):
        output = self.input(xi)
        error = tar - output
        self.w_[1:] += self.eta * xi.dot(error)
        self.w_[0] += self.eta * error
        cost = 0.5 * error ** 2
        return cost

    def partial_fit(self, X, y):
        if not self.w_initialized:
            self.initialized_weights(X.shape[1])
        if y.ravel().shape(0) > 1:
            for xi, tar in zip(X, y):
                self.updateweight(xi, tar)
        else:
            self.updateweight(X, y)
        return self

    def fit(self, X, y):
        self.initialized_weights(X.shape[1])
        self.cost = []
        for i in range(self.n_iter):
            if self.shuffle:
                X, y = self._shuffle(X, y)
            cost = []
            for xx, tar in zip(X, y):
                cost.append(self.updateweight(xx, tar))
            avg_cost = sum(cost) / len(y)
            self.cost.append(avg_cost)
        return self

    def score(self, Y_t, Y_form):
        cnt = 0
        dim = 0
        for i,j in Y_t,Y_form:
            if i==j:
                cnt+=1
            dim+=1
        return cnt*1.0/dim*1.0


def doctocsv(pathpos, pathneg, pathsave):
    np.random.seed(0)
    df = pd.DataFrame()
    for lines in open(pathpos, 'rb'):
        lines = lines.strip()[2:]
        lines = lines.strip()[:-2]
        df = df.append([[lines, 1]],ignore_index=True)
    for lines in open(pathneg, 'rb'):
        lines = lines.strip()[2:]
        lines = lines.strip()[:-2]
        df = df.append([[lines, 0]], ignore_index=True)
    df = df.reindex(np.random.permutation(df.index))
    df.to_csv(pathsave)
    return df

def yieldtocsv(csvpath):
    f = open(csvpath, 'r')
    next(f)
    next(f)
    # next(f)
    for lines in f:
        # print(lines)
        text = lines[:-3]
        labels=int(lines[-2])
        yield text,labels
    
def preprocessing(text):
    stopword = stopwords.words('english')
    text = text.strip()
    text = re.sub(r'[\W]+',' ',text.lower())
    tmp = [word for word in text.split() if not(word in stopword)]
    return tmp

def getdocstream(stra, datalength):
    doc, label = [], []
    try:
        for x in range(datalength):
            text, la= next(stra)
            doc.append(text)
            label.append(la)
        return doc, label
    except:
        return None, None

# local state

# from sklearn.linear_model import SGDClassifier
docvect = HashingVectorizer(decode_error='ignore', n_features=(2 ** 20), preprocessor=None, tokenizer=preprocessing)
sgc = SGDClassifier(loss='log', random_state=1, n_iter=1)
yc = yieldtocsv('D://data//movie_data.csv')
clas = np.array([0, 1])
pb = pyprind.ProgBar(50)
for x in range(50):
    X_t, Y_t = getdocstream(yc, 100)
    if not X_t:
        break
    X_t = docvect.transform(X_t)
    sgc.partial_fit(X_t, Y_t, classes=clas)
    pb.update()


ans = input("training test?(y/n)")
if ans=='y':
    X_ts, Y_ts = getdocstream(yc, 500)
    X_ts = docvect.transform(X_ts)
    print('Acc:' , sgc.score(X_ts, Y_ts))

ans = input("training dat?(y/n)")
if ans=='y':
    f = open('D://data//test', 'rb')
    Wr = open('D://data//ans', 'w')
    for line in f:
        X_tt = docvect.transform(line)
        ans = sgc.predict(X_tt)
        pro = sgc.predict_proba(X_tt)
        print("1 \t")
        if ans >= 0.5:
            print(1)
            print("  "+pro)
            print("\n")
        else:
            print(0)
            print("  "+pro)
            print("\n")

'''
base = 1000
cor = 0.87
'''