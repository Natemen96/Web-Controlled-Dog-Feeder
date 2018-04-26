#!/usr/bin/python
import tempfile
import os
from random import choice
import time

ext2conttype = {
"jpg": "image/jpeg",
"jpeg": "image/jpeg",
"png": "image/png",
"gif": "image/gif"
}

def content_type(filename):
    return ext2conttype[filename[filename.rfind(".")+1:].lower()]

def isimage(filename):
    #turn if filename's extension is in content-type lookup
    filename = filename.lower()
    return filename[filename.rfind(".")+1:] in ext2conttype
def random_file(dir):
    #return the filename of a randomly chose image in dir
    images = [f for f in os.listdir(os.path.expanduser(dir)) ] #if isimage(f)
    return choice(images)
    #print images
def pick_file(dir):
    return null

#Function for changing a dogbowl color 
def randomval():
    file = open('./outputFile.txt', 'r')
    a = file.read(2)
    a = int(a)
    if (a >= 2048):
        return 2
    elif (a <= 512):
        return 0
    else:
        return 1

def pair(val, dir):
    images = [f for f in os.listdir(os.path.expanduser(dir)) ]
    return images[val]
def writefalse():
    val = 0
    with open('./feedme.txt', 'w+') as f2:
    	f2.write('%d' % val )


if __name__ == "__main__":
    writefalse()
    dir = "../HTML/Images/"
    while True:
        r = pair (randomval(), dir)
        file2 = open('../HTML/Images/Bowl.txt', 'w')

        file2.write(r)

        print r
