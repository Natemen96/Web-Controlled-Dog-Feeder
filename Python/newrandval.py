#!/usr/bin/python
import tempfile
import os
from random import choice
import time



def randomval():
    file = open('./outputFile.txt', 'r')
    #a = map(int, file.read(2))
    a = file.read(2)
    a = int(a)
    #print(type(a))
    #print(a)
    #file.close()
    if (a >= 2048):
        return 2
    elif (a <= 512):
        return 0
    else:
        return 1


if __name__ == "__main__":
    print(randomval())
