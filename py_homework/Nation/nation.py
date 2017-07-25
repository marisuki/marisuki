import numpy as np
import cmath
import pickle
import os
class nation:
    def __init__(self, text):
        self.dic = {}
        self.words = []
        index = 0
        for line in text:
            word = line.replace(':', ',').strip().split(',')
            self.words.append(word)
            self.dic[word[0]] = index
            if not (word[1] in self.dic):
                self.dic[word[1]] = [index]
            else:
                self.dic[word[1]].append(index)
            index += 1

    def pop_density(self):
        index = 0
        for item in self.words:
            self.words[index].append(float(item[2])/float(item[3]))
            index += 1

    def getdic(self):
        return self.dic

    def getwords(self):
        return self.words

    def printdic(self, path):
        fopen = open(path, "w")
        for word in self.words:
            string = str(str(word[0])+':')
            string += str(word[1])
            string += ','+str(word[2])+','+str(word[3])
            string += '\n'
            fopen.write(string)

pathsrc = 'D://UN'
path = 'D://programme//pythoncharm//NATION//nationsDict.dat'
Nation = nation(open(pathsrc, "r"))

output = open(path,'wb')
pickle.dump(Nation.getwords(), output)
output.close()
