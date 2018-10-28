import numpy as np
import random
import matplotlib.pyplot as plt


class logistic(object):
    def __init__(self, xdim=2, Wgaussian_hypo=False, independent=True):
        self.gussian = Wgaussian_hypo
        self.X_vdim = xdim  # dim = 1+xdim: exp(WTX)
        self.xvalue_independent = independent
        self.X_data = None
        self.X_test = None
        self.X = None
        self.test_label = None
        self.Y = None  # X:(dim, L)=X_data.T X_data:(L, dim) Y:(L, 1) X_test:(dim, l_test)
        self.global_value_initializer()

    def global_value_initializer(self):
        """
            Automatically generate train/test matrixes, if have the input from outside, apply val directly.
        """
        if self.xvalue_independent and self.X_vdim == 2:
            pos = np.random.multivariate_normal([0, 2], cov=[[1, 0], [0, 1]], size=500)  # pos
            neg = np.random.multivariate_normal([4, 0], cov=[[2, 0], [0, 2]], size=500)  # neg
        elif not self.xvalue_independent and self.X_vdim == 2:
            pos = np.random.multivariate_normal([0, 4], [[3, 1], [1, 4]], size=500)
            neg = np.random.multivariate_normal([4, 0], [[3, 2], [2, 4]], size=500)
        else:
            pos, neg = [], []
        mapping = [([1]+list(item1), 0) for item1 in pos]
        for item in neg:
            mapping.append(([1]+list(item), 1))
        np.random.shuffle(mapping)
        self.Y = []
        self.X_data = []
        for item in mapping:  # shuffle: reduce
            self.X_data.append(item[0])
            self.Y.append(item[1])
        self.X_test = np.matrix(self.X_data[int(len(self.X_data)*5/7):]).T
        self.X_data = np.matrix(self.X_data[:int(len(self.X_data)*5/7)])
        self.X = self.X_data.T
        self.test_label = np.matrix(self.Y[int(len(self.Y)*5/7):]).T
        self.Y = np.matrix(self.Y[:int(len(self.Y)*5/7)]).T

    def generate_W(self):
        return np.matrix([random.gauss(0, 0.1) for i in range(self.X_vdim+1)]).T

    def crossMatrix(self, X): # x: (?, dim): self.X.T, matrix
        """
            Generate Matrix:(Xi*Xj) for each sample l, return val: matrix(dim, dim, L)
        """
        ans = []
        for s in range(np.size(X, 0)):
            tmpans = []  # X[s]: matrix(1, dim)
            mask = np.eye(np.size(X, 1))
            for i in range(np.size(X, 1)):
                tmpans.append([np.sum(np.dot(X[s], mask[i].T)*np.dot(X[s], mask[j].T)) for j in range(np.size(X, 1))])
            ans.append(tmpans)
        return ans

    def Loss(self, W):
        return np.array(self.Y)*np.array(np.dot(self.X.T, W)) - np.log(1 + np.exp(np.dot(W.T, self.X))).T

    def gradLoss(self, W):  # W:(dim,1) Xi:(dim, 1) Y:(L, 1), X:(dim, L )
        return np.dot(self.X, (self.Y.T - (np.exp(np.dot(W.T, self.X))/(1 + np.exp(np.dot(W.T, self.X))))).T)

    def gradgradLoss(self, W):
        val = np.exp(np.dot(W.T, self.X))
        factor = (val/(np.array(1 + val)*np.array(1 + val))).T
        cross = self.crossMatrix(self.X.T)
        hessian = np.matrix(cross[0])*np.sum(factor[0])
        for i in range(1, np.size(factor, 0)):
            hessian += np.matrix(cross[i])*np.sum(factor[i])
        return hessian

    def newton_log(self, threshold=1e-8, alpha=1, lambdas=1e-2):
        W, val_hold = self.generate_W(), 0  # (dim, 1)
        while True:
            step = np.dot(self.gradgradLoss(W).I, self.gradLoss(W))
            if self.gussian:
                W += alpha*(step - lambdas*W)
            else:
                W += alpha*step
            print(W, np.sum(self.gradLoss(W)))
            if abs(np.sum(self.gradLoss(W))) <= threshold or val_hold - np.sum(self.gradLoss(W)) < 1e-5:
                break
            else: val_hold = np.sum(self.gradLoss(W))
        print(self.gradLoss(W))
        return W

    def gradient_descent(self, threshold=1e-4, alpha=5e-8, lambdas=1e-2):
        W = self.generate_W()
        while True:
            step = self.gradLoss(W)
            if self.gussian:
                W += alpha*(step - lambdas*W)
            else:
                W += alpha*step
            print(W)
            print(np.sum(self.gradLoss(W)))
            if abs(np.sum(self.gradLoss(W))) <= threshold:
                break
        return W

    def test(self, W):
        val = (1/(1+np.exp(np.dot(W.T, self.X_test)))).T
        expect = [int(np.sum(val[i]) < 0.5) for i in range(np.size(val, 0))]
        return 1 - abs(np.sum(abs(expect - self.test_label.T))/np.size(val, 0))

    def pr_plot(self, W, flag=""):
        if self.X_vdim == 2:
            w0, w1, w2 = np.sum(W[0]), np.sum(W[1]), np.sum(W[2])
            plt_X = np.linspace(np.min(self.X[1]), np.max(np.max(self.X[2])))
            plt_Y = [-w0/w2 - w1/w2*x for x in plt_X]
            mask = np.eye(3)
            scatter = [(np.sum(np.dot(item, mask[1])), np.sum(np.dot(item, mask[2]))) for item in self.X_data]
            print(scatter)
            label_pt = self.Y.T
            scat_pos = [[], []]
            scat_neg = [[], []]
            for i in range(len(scatter)):
                if np.sum(self.Y[i]) == 0:
                    scat_neg[0].append(scatter[i][0])
                    scat_neg[1].append(scatter[i][1])
                elif np.sum(self.Y[i]) == 1:
                    scat_pos[0].append(scatter[i][0])
                    scat_pos[1].append(scatter[i][1])
                else:
                    print("Error while map/reduce the points.")
            plt.scatter(scat_neg[0], scat_neg[1], s=75, alpha=.5, color='purple')
            plt.scatter(scat_pos[0], scat_pos[1], s=75, alpha=.5, color='orange')
            plt.plot(plt_X, plt_Y, color='green')
            plt.title("Logistic Regression: gussian:%s ind:%s %s test_res:%f" % (str(self.gussian), str(self.xvalue_independent), flag, self.test(W)))
            plt.savefig("LogisticRegression_gussian=%sind=%s%s.png" % (str(self.gussian), str(self.xvalue_independent), flag))
            plt.show()
        else:
            pass  # go to test


def wine_data_insert():
    f = open("winedata.csv", "r")
    classify, classify_test, X_data, X_test = [], [], [], []
    for line in f:
        line = line.split(",")
        # if int(line[0]) == 3: continue
        classify.append(int(line[0]) - 1)
        tmp = [1]
        for i in range(1, len(line)):
            tmp.append(float(line[i]))
        X_data.append((tmp, int(line[0]) - 1))
    random.shuffle(X_data)
    X_test = X_data[int(len(X_data)*5/7):]
    classify_test = [item[1] for item in X_test]
    X_test = [item[0] for item in X_test]
    X_data = X_data[:int(len(X_data)*5/7)]
    classify = [item[1] for item in X_data]
    X_data = [item[0] for item in X_data]
    f, fl = open("wine_test.txt", "w"), open("wine_test_label.txt", "w")
    for (item, label) in zip(X_test, classify_test):
        for it in item: f.write(str(it) + "\t")
        f.write("\n")
        fl.write(str(label) + "\n")
    f.close(), fl.close()
    fr, frl = open("wine_train.txt", "w"), open("wine_train_label.txt", "w")
    for (item, label) in zip(X_data, classify):
        for it in item: fr.write(str(it) + "\t")
        fr.write("\n")
        frl.write(str(label) + "\n")
    fr.close(), frl.close()
    return np.matrix(X_data), np.matrix(X_test).T, np.matrix(classify).T, np.matrix(classify_test).T


def ReadFromStandardFile(mask=0):
    X_train, X_test, Y_train, Y_test = [], [], [], []
    f, fl = open("wine_test.txt", "r"), open("wine_test_label.txt", "r")
    for line in f:
        line = line.split()
        X_test.append([float(line[i]) for i in range(0, len(line))])
    for line in fl:
        if mask != -1: Y_test.append([int(float(line) == mask)])
        else: Y_test.append([int(line)])
    fr, frl = open("wine_train.txt", "r"), open("wine_train_label.txt", "r")
    for line in fr:
        print(line)
        line = line.split()
        X_train.append([float(line[i]) for i in range(0, len(line))])
    for line in frl:
        Y_train.append([int(float(line) == mask)])
    return np.matrix(X_train), np.matrix(Y_train), np.matrix(X_test).T, np.matrix(Y_test)


def decision_tree():  # precision: 0.705882
    # classify label 1 first(original:2), then classify label 0 (ori:1), the other point is label 2 (ori:3)
    W_cl1 = [[-0.19624184], [0.14048495], [-0.32750738], [0.04732983], [0.1123163], [0.02439485], [0.0467235],
             [0.09784779], [0.04087847], [-0.18535481], [-0.23524893], [-0.08212339], [-0.05971632], [-0.00696094]]
    W_cl0 = [[0.0187151], [0.00048866], [-0.10105207], [0.06552508], [-0.46800525], [-0.04441048], [-0.02615863],
             [0.13665488], [0.08469632], [-0.00764128], [-0.05588578], [-0.02218694], [0.03718035], [0.01629198]]
    W_cl1 = np.matrix(W_cl1)
    W_cl0 = np.matrix(W_cl0)
    X_test, Y_test = [], []
    f, fl = open("wine_test.txt", "r"), open("wine_test_label.txt", "r")
    for line in f:
        line = line.split()
        X_test.append([float(line[i]) for i in range(0, len(line))])
    for line in fl:
        Y_test.append(int(line))
    X_test = np.matrix(X_test).T
    val1 = (1/(1+np.exp(np.dot(W_cl1.T, X_test)))).T
    expect1 = [int(np.sum(val1[i]) < 0.5) for i in range(np.size(val1, 0))]
    val0 = (1/(1+np.exp(np.dot(W_cl0.T, X_test)))).T
    expect0 = [int(np.sum(val0[i]) < 0.5) for i in range(np.size(val0, 0))]
    print(expect0)
    print(expect1)
    print(Y_test)
    ans = []
    for i in range(0, len(expect0)):
        if expect1[i] == 1:
            ans.append(1)
        elif expect0[i] == 1:
            ans.append(0)
        else:
            ans.append(2)
    cnt = 0
    print(ans)
    for i in range(0, len(ans)):
        if ans[i] == Y_test[i]:
            cnt += 1
    print("Precision = %lf" % (cnt/len(ans)))
    return cnt/len(ans)


if __name__ == "__main__":
    """
        Normal Train, test
    """
    log = logistic(Wgaussian_hypo=True, independent=True)
    w = log.gradient_descent()
    print("RES:")
    print(w)
    log.pr_plot(w, "testgrad")

    """
        Train, test from dataset: UCI: https://archive.ics.uci.edu/ml/machine-learning-databases/wine
        classify 0: W :0.90196
        [[ 0.11116817]
 [-0.18515697]
 [ 0.05445636]
 [-0.07500515]
 [-0.41380713]
 [-0.03442779]
 [ 0.09983258]
 [ 0.01055378]
 [-0.01554494]
 [ 0.02209726]
 [-0.07036363]
 [ 0.0266265 ]
 [ 0.0548774 ]
 [ 0.01650266]]
        classify:1 W :0.882352941176
        [[ 0.0088141 ]
 [ 0.00994699]
 [-0.1510287 ]
 [ 0.0400127 ]
 [ 0.15663027]
 [ 0.02726139]
 [ 0.10969113]
 [ 0.27900054]
 [ 0.06219452]
 [ 0.15556723]
 [-0.54909899]
 [ 0.12975475]
 [ 0.2285545 ]
 [-0.0077714 ]]
    class 2: 0.90196
    
    class 1-> 0: 0.705882
    class 2
    
    log = logistic(xdim=13)
    # log.X_data, log.X_test, log.Y, log.test_label = wine_data_insert()
    log.X_data, log.Y, log.X_test, log.test_label = ReadFromStandardFile(mask=2)  # 1
    log.X = log.X_data.T
    print(log.X)
    print(log.Y)
    print(log.test_label)
    w = log.gradient_descent(threshold=1e-5)
    print(log.test(w))
    decision_tree()"""

