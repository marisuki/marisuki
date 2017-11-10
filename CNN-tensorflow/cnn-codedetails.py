import tensorflow as tf
import numpy as np
import matplotlib.pyplot as plt
import os
import re
import sys

#image read process

def solve_extend(path):
    cpy = path.strip()
    cpy = re.sub(r'.[\W]+', ' ', cpy.lower())
    return cpy.split()[-1]


def tf_readimage(path):
    try:
        image_raw = tf.gfile.FastGFile(path, 'rb').read()
        extend_name = solve_extend(path)
        print(extend_name)
        with tf.Session() as sess:
            if extend_name == 'jpg' or extend_name == 'jpeg':
                image_data = tf.image.decode_jpeg(image_raw)
            elif extend_name == 'png':
                image_data = tf.image.decode_png(image_raw)
            elif extend_name == 'gif':
                image_data = tf.image.decode_gif(image_raw)
            else:
                return [0]
            image_data = tf.image.convert_image_dtype(image_data, dtype = tf.uint8)
            #print(image_data.eval())
            #plt.imshow(image_data.eval())
            #plt.show()
            # f = open('D://programme//ans.dat','w')
            #f.write(str(image_data.eval()))
            #print(np.shape(image_data.eval()))
            return image_data.eval()
    except Exception:
        return [-1]

def gen_tf_image(path):
    data = tf_readimage(path)
    #print(data)
    shape = np.shape(data)
    #print(shape)
    #print(np.shape(shape))
    if shape==(1,):
        print("ERROR: invalid dataset: end")
        return 0
    print('INFO: valid dataset: start processing...')
    return data
#print(gen_tf_image("C://Users//RuiKang//Downloads//olivettifaces.gif"))
# data = tf_readimage('D://picture_script//170918a.png')
# data[x][y][:3]=RGB(image)

def cut_image(path, shapes, general=[1]): #shapes=[height, width], general=[numCX],57*47
    data = gen_tf_image(path)
    print('INFO: processing: input='+str((np.shape(data)))) 
    if np.shape(shapes) != (2,):
        return False
    shape_data = np.shape(data)
    shape_shape_data = np.shape(shape_data)
    numX = int(shape_data[-2]/shapes[1])
    numY = int(shape_data[-3]/shapes[0])
    print('INFO: cut into= '+str([numX, numY])) 
    image = []
    single = []
    for j in range(1,numY+1):
        for i in range(1, numX+2):
            posX_st = (i-1)*shapes[1]
            posX_ed = (i)*shapes[1]
            posY_st = (j-1)*shapes[0]
            posY_ed = (j)*shapes[0]
            if i==11 or (i==21):
                image.append(single)
                single=[]
                if i==21:
                    continue
            imag=[]
            for posYY in range(posY_st, posY_ed):
                #print(np.shape(data[0][posYY][posX_st:posX_ed]))
                imag.append(list(data[0][posYY][posX_st:posX_ed]))
            single.append([imag])
            #print('INFO: case'+str(j)+str(np.shape(image)))
    for i in range(0,40):
        print(str(i)+':')
        print(np.shape(image[i]))
    return image
#image = cut_image(path="C://Users//RuiKang//Downloads//olivettifaces.gif",shapes=[57,47],general=[10])
#print(np.shape(image))

#handling the image to matrix

import random
import math
from PIL import Image

def make_group(path, shapes, general=[1]):
    image = cut_image(path, shapes, general) #6:4=train:test
    class_train = []
    label_train = []
    class_test = []
    label_test = []
    class_vaild = []
    label_vaild = []
    for i in range(0, 40):
        # print(image[i][1][0][1][1])
        random.shuffle(image[i])
        label = list(np.zeros(40))
        label[i]=1
        # print(image[i][1][0][1][1])
        # print(np.shape(image[i][7:]))
        class_train.append(image[i][:7])
        class_test.append(image[i][7:9])
        class_vaild.append(image[i][9])
        for xx in range(0,7):
            label_train.append(label)
        for xx in range(0,2):
            label_test.append(label)
        label_vaild.append(label)
    #print(class_train[2][1][0])
    #tmp = np.dot(class_train,np.eye(240))
    #print(class_train[2][1][0])
    #class_train = theano.shared()
    print('out validation:'+str(np.shape(class_vaild)))
    return class_train[:], class_test[:], class_vaild, label_train, label_test, label_vaild

#a,b,c,d = make_group(path="C://Users//RuiKang//Downloads//olivettifaces.gif",shapes=[57,47],general=[10])
#print(np.shape(a))
#print(np.shape(a[0]))
#print(np.shape(a[38]))
#print(np.shape(b[0]))
#print(np.shape(b))
#print(c[6])

import tensorflow as tf

# import tensorflow.examples.tutorials.mnist.input_data as input_data
# structure = {c+pool1:3600-,}

def max_pool(inputs):
    return tf.nn.max_pool(inputs, ksize=[1,2,2,1], strides=[1,2,2,1], padding='SAME')

def tf_conv2(inputs, W):
    return tf.nn.conv2d(inputs, W, strides=[1,1,1,1], padding='SAME')

def weight_variable(shape):
    initial = tf.truncated_normal(shape, stddev=0.1)
    return tf.Variable(initial)

def bias_variable(shape):
    initial = tf.constant(0.1, shape=shape)
    return tf.Variable(initial)

class opt(object):
    def __init__(self):
        self.steps = 0.1
        self.batch = 7
        self.epochs = 1000
        self.early_stop_patience = 10
        self.kind = 40
        self.test_size = 3
        self.validation = 0


class image_feed(object):
    def __init__(self, start=-1, batch_size=7):
        self.pos = start
        self.batch = batch_size
        self.total = 40
        self.x_train, self.x_test, self.x_valid, self.y_train, self.y_test, self.y_valid = make_group(path="C://Users//RuiKang//Downloads//olivettifaces.gif",shapes=[57,47],general=[10])
        for i in range(0,40):
            for j in range(0,7):
                self.x_train[i][j] = self.x_train[i][j][0]
        #print(np.shape(self.y_train))
        print(np.shape(self.y_test))
        for i in range(0,40):
            for j in range(0,2):
                self.x_test[i][j] = self.x_test[i][j][0]
        for i in range(0,40):
            self.x_valid[i]=self.x_valid[i][0]
        print('out valid in : '+str(np.shape(self.x_valid)))
        '''for i in range(0,40):
            for j in range(0,1):
                self.x_valid[i] = self.x_valid[i][0]'''
       # print('x_test: '+str(np.shape(self.x_test)))
        
    def feed_next_train(self, nextpos=1):
        self.pos += nextpos
        return self.x_train[self.pos], self.y_train[self.pos*7:(self.pos+1)*7]
    
    def feed_next_test(self, st=0, ed=40):
        x_te = self.x_test[st]
        print(np.shape(self.y_test))
        for i in range(st+1, ed):
            for j in range(0,2):
                x_te.append(self.x_test[i][j])
        return x_te, self.y_test
    
    def feed_next_valid(self):
        return self.x_valid, self.y_valid
    
#x_train, x_test, y_train, y_test = make_group(path="C://Users//RuiKang//Downloads//olivettifaces.gif",shapes=[57,47],general=[10])
#label: one_hot=True
#x_train: [40,7,1,]
'''
for i in range(0,40):
    for j in range(0,7):
        x_train[i][j] = x_train[i][j][0]

#print(np.shape(x_train))
for i in range(0,40):
    for j in range(0,3):
        x_test[i][j] = x_test[i][j][0]
#print(np.shape(x_test))
#print(np.shape(y_train))
#print(np.shape(y_test))
'''
image = image_feed()
x_test,y_test = image.feed_next_test()
print('x_test: '+str(np.shape(x_test)))
print('y_test: '+str(np.shape(y_test)))
#print('y_train: '+str(np.shape(y_train)))
#for i in range(0,40):print(np.shape(x_test[i]))
#x_valid, y_valid = image.feed_next_valid()
#print(y_valid)
#print(np.shape(x_valid))
# end image generator

def compute_accuracy(x,y):
    global prediction
    y_pre = sess.run(prediction, feed_dict={x_im : x, keep_prob:1})
    correct_prediction = tf.equal(tf.argmax(y_pre, 1), tf.argmax(y, 1))
    accuracy = tf.reduce_mean(tf.cast(correct_prediction, tf.float32))
    result = sess.run(accuracy, feed_dict={x_im: x, y_: y, keep_prob:1})
    return result

params = opt()
#xs = tf.placeholder(tf.float32, [None, 2679]) # 57*47
#initalize cnn params
#x_im = tf.placeholder(tf.float32, [None, 57,47,3])
#y_ = tf.placeholder(tf.float32, [None, 40])
#keep_prob = tf.placeholder(tf.float32)
#framework:
def model(x_im, y_):
    #print(y_[0])
    #cnn1
    W_conv1 = weight_variable([5,5,1,50])   #input:57*47 => output:52*42
    b_conv1 = bias_variable([50]) # input:52*42 => 26*21
    h_conv1 = tf.nn.relu(tf_conv2(x_im, W_conv1)+b_conv1)
    h_pool1 = max_pool(h_conv1)
    #print(np.shape(h_pool1))
    #cnn2
    W_conv2 = weight_variable([2,2,50,50])    #input: 26*21  => 24*19
    b_conv2 = bias_variable([50])        #24*19   =>12*9
    h_conv2 = tf.nn.relu(tf_conv2(h_pool1, W_conv2)+b_conv2)
    h_pool2 = max_pool(h_conv2)
    #cnn3
    W_conv3 = weight_variable([2,2,50,50]) #11*8
    b_conv3 = bias_variable([50])   #5*4
    h_conv3 = tf.nn.relu(tf_conv2(h_pool2, W_conv3)+b_conv3)
    h_pool3 = max_pool(h_conv3)
    #fc1
    W_fullcon1 = weight_variable([2400, 200])
    b_fullcon1 = bias_variable([200])
    h_pool3_reshape = tf.reshape(h_pool3, [-1, 2400])
    h_fullcon1 = tf.nn.relu(tf.matmul(h_pool3_reshape, W_fullcon1)+b_fullcon1)
    #fc2
    h_fc1_dropout = tf.nn.dropout(h_fullcon1, keep_prob)
    W_fc2 = weight_variable([200, 40])
    b_fc2 = bias_variable([40])
    prediction = tf.nn.softmax(tf.matmul(h_fc1_dropout, W_fc2)+b_fc2)
    print(prediction)
    rmse = tf.sqrt(tf.reduce_mean(tf.square(y_-prediction)))
    #cross entropy
    #cross_entropy = tf.reduce_mean(-tf.reduce_sum(y_ * tf.log(prediction), reduction_indices=[1]))
    #train_step = tf.train.AdamOptimizer(params.steps).minimize(cross_entropy)
    return prediction, rmse

'''
#sess.run(tf.global_variables_initializer())
image = image_feed()
x_train, y_train = image.feed_next_train()
#print(x_train[1])
#print(y_train[1])
for i in range(7):
    print('x,y shape={0},{1}'.format(np.shape(x_train[i]),y_train[i][0]))
for i in range(7):
    print(y_train[i])

x_tr = []
for k in range(0,7):
    imag = []
    line = []
    for i in range(0,57):
        line = []
        for j in range(0,47):
            line.append([(x_train[k][i][j][0]*30 + x_train[k][i][j][1]*59 + x_train[k][i][j][2]*11+50)/100])
        imag.append(line)
    x_tr.append(imag)
print(np.shape(x_tr))
predict, loss = model(x_tr, y_train)
print('prediction = {0}'.format(predict))
print('loss = {0}'.format(float(loss)))

for i in range(params.epochs+1):
    print('epoch for '+str(i+1)+' case...')
    x_t, y_t = image.feed_next_train()
    print(np.shape(y_t))
    for ix in range(0,min(np.shape(x_t)[0],np.shape(y_t)[0])):
        print(y_t[ix])
        sess.run(train_step, feed_dict={x_im: [x_t[ix]] , y_: [y_t[ix]]  , keep_prob : 0.5 })
    x_test, y_test = image.feed_next_test()
    #print((y_test))        
    #print((x_test[1]))
    accur=0
    for m in range(0,40):
        accur += compute_accuracy([x_test[m]], [y_test[m]])
    print('accuracy for test '+str(i+1)+'  : '+str(accur/40))
'''

import pandas as pd
import numpy as np

def save_model(saver, sess, save_path):
    path = saver.save(sess, save_path)
    print('model swave in :{0}'.format(path))

image = image_feed()
SAVE_PATH = 'model'
if __name__=='__main__':
    x_im = tf.placeholder(tf.float32, [None, 57,47,1])
    y_ = tf.placeholder(tf.float32, [None, 40])
    keep_prob = tf.placeholder(tf.float32)
    sess = tf.InteractiveSession()
    predict, rmse = model(x_im,y_)
    train_step = tf.train.AdamOptimizer(1e-3).minimize(rmse)
    sess.run(tf.initialize_all_variables())
    saver = tf.train.Saver()
    valid_max=1e9+7
    print('I: training begin...')
    for t in range(0,40):
        x_train, y_train = image.feed_next_train()
        x_valid, y_valid = image.feed_next_valid()
        x_tr = []
        for k in range(0,7):
            imag = []
            for i in range(0,57):
                line = []
                for j in range(0,47):
                    line.append([(x_train[k][i][j][0]*30 + x_train[k][i][j][1]*59 + x_train[k][i][j][2]*11+50)/100])
                imag.append(line)
            x_tr.append(imag)
        x_train = x_tr
        x_tr = []
        for k in range(0,1):
            imag = []
            for i in range(0,57):
                line = []
                for j in range(0,47):
                    line.append([(x_valid[k][i][j][0]*30 + x_valid[k][i][j][1]*59 + x_valid[k][i][j][2]*11+50)/100])
                imag.append(line)
            x_tr.append(imag)
        x_valid = x_tr
        print('x_train config:{0}'.format(np.shape(x_train)))
        print(np.shape(x_valid))
        train_loss = 0
        valid_loss = 0
        print('epoch on train {0} of {1}...'.format(t,40) )
        print(np.shape(x_train), (y_train))
        train_step.run(feed_dict = {x_im: x_train, y_:y_train, keep_prob:0.5})
        for j in range(0,7):
            train_loss += rmse.eval(feed_dict={x_im:x_train, y_:y_train, keep_prob:1})
        for j in range(0,40):
            valid_loss += rmse.eval(feed_dict={x_im:x_valid, y_:y_valid, keep_prob:1.0})
        if valid_loss < valid_max : 
            valid_max = valid_loss
            #save_model(saver,sess,SAVE_PATH)
            '''
        else :
            print('early stopped.')
            break
            '''
        print('train on {0} done, train_loss = {1}. '.format(i+1, train_loss))
    y_pred = []
    x_test, y_test = image.feed_next_test()
    x_tr = []
    for k in range(0,80):
        imag = []
        for i in range(0,57):
            line = []
            for j in range(0,47):
                line.append([(x_test[k][i][j][0]*30 + x_test[k][i][j][1]*59 + x_test[k][i][j][2]*11+50)/100])
            imag.append(line)
        x_tr.append(imag)
    x_test = x_tr
    print(np.shape(x_test))
    print('y_test:{0}'.format(np.shape(y_test)))
    acc = 0
    for j in range(0,40):
        for i in range(0,2):
            y_batch = predict.eval(feed_dict={x_im:[x_test[j]], y_:[y_test[j]], keep_prob:1.0})
            print(y_batch)
            pred = (y_batch==(np.max(y_batch)))
            print(y_test[j])
            for k in range(0,40):
                if int(y_batch[0][k])!=int(y_test[j][k]):
                    continue
                else :
                    acc = acc + 1
    print('accuracy predict = : '+str(acc/80))
    
