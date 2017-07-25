import cmath
import os
import matplotlib.pyplot as plt
import nation
import re

Nation = nation.nation(open('D://programme//pythoncharm//NATION//nationsDict.dat', "r"))
print(Nation.getdic())
Nation.pop_density()
print(Nation.getwords())

contient = input("Enter a contient: ")
lis = Nation.getwords()
dic = Nation.getdic()


def func():
    lism = []
    for y in dic[contient]:
        lism.append(lis[y])
    lism.sort(key = lambda x: x[4], reverse= True)
    listt = lism[:9]
    X = []
    Y = []
    label = []
    cnt = 1.00
    for it in listt:
        X.append(cnt)
        label.append(it[0])
        Y.append(it[4])
        cnt += 1

    fig, ax = plt.subplots()
    ax.bar(X,Y)
    for i, str in enumerate(label):
        ax.annotate(str, (X[i]-0.50, Y[i]))

    plt.show()

func()