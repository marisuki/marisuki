import numpy as np
import matplotlib.pyplot as plt


class hyperparams(object):
    def __init__(self, dim, X_samp, Y_samp, alpha, lambdas=None):
        """
        Params, Datas

        :param dim: generate dimsion to fitting: f(x) = \sum wi*x^i, i \in {0,1.. dim}
        :param X_samp:
        :param Y_samp:
        :param alpha:learning rate,
        :param lambdas:regularization hyperparam if is none, the program will either
                        choose one from valid range or just test/ignore regular
        """
        self.lambdas = lambdas
        self.dim = dim
        self.X_samp = X_samp
        self.Y_samp = Y_samp
        (self.X_train, self.Y_train), (self.X_valid, self.Y_valid), (self.X_test, self.Y_test) = self.data_split()
        self.X = self.matrix_X_gener()
        self.alpha = alpha
        self.cnt = 0
        self.Y_train = np.transpose(self.Y_train)

    def data_split(self):
        """
        Split the whole dataset into 3 parts: train, valid, test = 9:4:1
        :return:
        """
        return (self.X_samp[:np.int32(9*len(self.X_samp)/14)], self.Y_samp[:np.int32(9*len(self.X_samp)/14)]), (self.X_samp[np.int32(9*len(self.X_samp)/14): np.int32(13*len(self.X_samp)/14)], self.Y_samp[np.int32(9*len(self.X_samp)/14): np.int32(13*len(self.X_samp)/14)]), (self.X_samp[np.int32(13*len(self.X_samp)/14):], self.Y_samp[np.int32(13*len(self.X_samp)/14):])

    def matrix_X_gener(self, ori=None):
        """
        Generate the vandmonde matrix. from X_train or other origin
        :param ori: X
        :return: vand-mat
        """
        if ori is None:
            ori = self.X_train
        tmp = [1 for i in range(0, len(ori))]
        ans = [tmp]
        for i in range(1, self.dim):
            tmp = [i*j for (i, j) in zip(tmp, ori)]
            ans.append(tmp)
        X = np.matrix(ans).T
        return X

    def solve_W_direct(self, regular=True):
        XT = np.transpose(self.X)
        XTX = np.dot(XT, self.X)
        XTY = np.dot(XT, np.matrix(self.Y_train).T)
        if not regular or self.lambdas is None:
            W = np.dot(np.matrix(XTX).I, np.matrix(XTY))
            return W
        else:
            W = np.dot(np.matrix(XTX+self.lambdas*np.eye(self.dim)).I, np.matrix(XTY))
            return W

    def pr_plot(self, w, X_smp=None, Y_smp=None, attached_flags=""):
        """
        Making graphics, w is params and X,Y_smp is always the whole dataset: used to plot the points.
        :param w:
        :param X_smp:
        :param Y_smp:
        :param attached_flags: labels to classify the method used to generate the W.
        :return:
        """
        self.cnt += 1
        if X_smp == None or Y_smp == None:
            X_smp = self.X_samp
            Y_smp = self.Y_samp
        plt.scatter(X_smp, Y_smp, s=75, c='green', alpha=.5)
        X_map = np.linspace(np.min(self.X_samp), np.max(self.X_samp))
        XY_exm = self.hypothesis(w, X_map)
        plt.plot(X_map, XY_exm, color='blue')
        plt.xticks(np.linspace(np.min(X_smp), np.max(X_smp), 11, endpoint=True))
        plt.yticks(np.linspace(np.min(Y_smp), np.max(Y_smp), 11, endpoint=True))
        plt.title("Hypothesis: siz=%(size)d dim=%(dim)d  lambda=%(lam).4f  loss=%(los).4f  %(fla)s" %
                  {'size': len(self.X_samp)/100, 'dim': self.dim, 'lam': self.lambdas, 'los': self.evaluate(w), 'fla': attached_flags})
        plt.savefig("Figure_Hyp dim%(dim)d lam%(lam).4f %(fla)s .png" % {'dim': self.dim, 'lam': self.lambdas, 'fla': attached_flags})
        plt.show()

    def evaluate(self, W, testX=None, testY=None):
        """
        Generate test for W, maybe use the dataset from valid or test,
        if testX,Y are not attached with one value, then use the test data,
        else use the valid(or attached): used in evaluating the lambda.
        :param W:
        :param testX:
        :param testY:
        :return:
        """
        if testX is None or testY is None:
            testX = self.X_test
            testY = self.Y_test
        Y_exm = self.hypothesis(W, testX)
        loss = np.sum([(y-y_)**2 for (y, y_) in zip(Y_exm, testY)])
        return loss/len(testX)

    def evaluate_lambda(self, max_lambda, user_method=solve_W_direct, flag=""):
        """
        Test lambda to find a better fitting,
        :param max_lambda: max range of lambda
        :param user_method: choice of method to hypothesis
        :param flag: used for graph making
        :return:
        """
        Loss = []
        Lambda = []
        evalu = 0x3fffffff
        store_lambda = 0
        for fl in range(0, int(max_lambda*100), 2):
            fl *= 0.01
            self.lambdas = fl
            tmp = self.evaluate(user_method(self), testX=self.X_valid, testY=self.Y_valid)
            Lambda.append(fl)
            Loss.append(tmp)
            if tmp == min(tmp, evalu):
                store_lambda = fl
                evalu = min(tmp, evalu)
        self.lambdas = store_lambda
        plt.plot(Lambda, Loss)
        plt.title("lambda evaluate: dsize=%(size)d dim=%(dim)d Optimizedlam=%(Opt).4f %(flags)s" % {'size': len(self.X_samp)/100, 'dim': self.dim,  'Opt': self.lambdas, 'flags': flag})
        plt.savefig("lambda evaluate dsize%(size)d dim%(dim)d Opt%(Opt).4f %(flags)s .png" % {'size': len(self.X_samp)/100, 'dim': self.dim,  'Opt': self.lambdas, 'flags': flag})
        plt.show()
        return store_lambda, evalu

    def hypothesis(self, W, x):
        XX = self.matrix_X_gener(ori=x)
        return np.dot(XX, W)

    def xavier_initializer(self):
        val = np.sqrt(3/len(self.X_train))
        return np.matrix([np.random.uniform(low=-val, high=val) for i in range(self.dim)]).T

    def solve_W_GD(self, regular=True, W=None):
        """
        Gradient Descent: loss = (0.5*(XW-Y)T(XW-Y) + lambda*0.5*WTW)/m
        \frac{\partial loss}{\partial W} = gradW = (XTXW - XTY + lambda*I*W)/m
        self.alpha: learning rate
        Weight initializer = xavier_initializer
        :param regular:
        :return:
        """
        if W is None:
            W = np.zeros([self.dim, 1])

        if regular is True and self.lambdas is None:
            self.lambdas = np.random.normal(loc=0.5, scale=0.4)
            print("select lambda as:" + str(self.lambdas))

        cntt = 0
        while True:
            bias = (np.dot(self.X, W) - np.matrix(self.Y_train).T)/len(self.X_train)  # size*1
            grad = np.dot(self.X.T, bias) + self.lambdas * W
            W = W - self.alpha * grad
            cntt += 1
            loss = self.evaluate(W)
            if cntt == 1000 or loss <= 1e-4:
                break
            if cntt % 1000 == 0:
                print(str(cntt/100) + "data:")
                print(loss)
                print(W)
        return W

    def solve_W_tf(self, regular=True):
        """
        Tensorflow: 1.2.0 py3.5
        GD using Adam Optim from TF
        :param regular:
        :return:
        """
        if not regular:
            return
        import tensorflow as tf
        if self.lambdas is None:
            self.lambdas = np.random.normal(0.5, 0.3)
        x = tf.placeholder(tf.float32, shape=(len(self.X_train), self.dim))
        y = tf.placeholder(tf.float32, shape=(len(self.Y_train), 1))
        W = tf.Variable(tf.zeros([self.dim, 1]))
        pred = tf.matmul(x, W)
        cost = tf.reduce_mean(tf.reduce_sum(tf.matmul(tf.transpose(pred-y), pred-y))+tf.multiply(self.lambdas, tf.matmul(tf.transpose(W), W)))
        train = tf.train.AdamOptimizer().minimize(cost)
        sess = tf.Session()
        sess.run(tf.global_variables_initializer())
        for i in range(10000):
            sess.run([train, W], feed_dict={x: self.X, y: np.matrix(self.Y_train).T})
            if i % 100 == 0:
                print(sess.run(W))
            end = sess.run(W)
        plt.scatter(self.X_samp, self.Y_samp, alpha=.5, color='green', s=75)
        self.pr_plot(end, attached_flags="tf")
        return end

    def solve_W_conjuct(self, regular=True, jumpout=0.01):
        """
        Conjugate GD

        :param regular:
        :param jumpout: lower bound of gener_los
        :return:
        """
        if not regular:
            return
        Q = np.matrix(np.dot(self.X.T, self.X) + self.lambdas*np.eye(self.dim))
        x = self.xavier_initializer()
        b = np.dot(self.X.T, np.matrix(self.Y_train).T)
        r = b - np.dot(Q, x)
        d = r
        k = 0
        while k < 5000000:
            alpha = np.sum(np.dot(r.T, r)/np.dot(np.dot(d.T, Q), d))
            x += alpha*d
            r_tmp = r - alpha*np.dot(Q, d)
            if np.sum(np.dot(r_tmp.T, r_tmp)/np.shape(r_tmp)) <= jumpout:
                break
            beta = np.sum(np.dot(r_tmp.T, r_tmp)/np.dot(r.T, r))
            d = r_tmp + beta*d
            r = r_tmp
            k += 1
            if k % 100 == 0:
                print(self.evaluate(x))
                print(x)
        return x


def data_generator(bias=0.01, random='guss', min=0.0, max=2*np.pi):
    X = np.arange(min, max, bias)
    np.random.shuffle(X)
    X = list(X)
    Y = np.sin(X)
    for i in range(len(X)):
        if random == 'uniform':
            Y[i] += np.random.uniform(low=0.0, high=1.0)
        else:
            Y[i] += np.random.normal(loc=0.0, scale=0.2)
    return X, Y


if __name__ == '__main__':
    X_tmp, Y_tmp = data_generator(bias=0.02)
    hy = hyperparams(int(6), X_tmp, Y_tmp, 0.02, 0.05)
    w = hy.solve_W_conjuct()
    hy.pr_plot(w, attached_flags="conj1")
    hy = hyperparams(int(6), X_tmp, Y_tmp, 0.02, 0.01)
    w = hy.solve_W_conjuct()
    hy.pr_plot(w, attached_flags="conj2")
    hy = hyperparams(int(6), X_tmp, Y_tmp, 0.02, 0.1)
    w = hy.solve_W_conjuct()
    hy.pr_plot(w, attached_flags="conj3")
    hy.evaluate_lambda(10.0, user_method=hy.solve_W_conjuct, flag="conj")
    w = hy.solve_W_conjuct()
    hy.pr_plot(w, attached_flags="conjugate")
    print(hy.evaluate(w))

    X_tmp, Y_tmp = data_generator(bias=0.01)
    hy = hyperparams(int(10), X_tmp, Y_tmp, 0.02, 0.0)
    W = hy.solve_W_direct()
    hy.pr_plot(W, attached_flags="DirUnReg")

    print(hy.evaluate_lambda(10, flag="DIR"))
    W = hy.solve_W_direct()
    hy.pr_plot(W, attached_flags="lambdaOPDR")
    
    X_tmp, Y_tmp = data_generator()
    hy = hyperparams(5, X_tmp, Y_tmp, 0.0000002, 0.05)
    W = hy.solve_W_GD(W=np.matrix([0.03785995, 1.26832123, -0.55128356,0.01908278,0.01176263]).T)
    hy.pr_plot(W, attached_flags="GD")
    print(W)
    
    X_tmp, Y_tmp = data_generator()
    hy = hyperparams(5, X_tmp, Y_tmp, 0.01)
    W = hy.solve_W_tf()
    hy.pr_plot(W, attached_flags="TensorFAdam")
    print(W)