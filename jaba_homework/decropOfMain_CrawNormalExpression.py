# -*- coding: utf-8 -*-
import re
import sys

class proc:
    def __init__(self, filenameopen, filenamesave):
        self.fileopen = filenameopen
        self.filesave = filenamesave
    def solve(self):
        pattern = r'<d p=.*?>(.*?)</d>'
        f = open(self.fileopen, 'rb')
        fr = open(self.filesave, 'w+')
        for line in f:
            try:
                line = str(line.decode('utf-8'))
            except:
                pass
            line = re.findall(pattern, line)
            print(line)
            try:
                fr.writelines(line)
            except:
                print(line+"except")



proc(sys.argv[1], sys.argv[2])
