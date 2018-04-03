import os
from random import choice
ext2conttype = {"jpg": "image/jpeg",
"jpeg": "image/jpeg",
"png": "image/png",
"gif": "image/gif" }

def content_type(filename):
    return ext2conttpe[filename[filename.rfind(".")+1:].lower()]

def isimage(filename):
    #turn if filename's extension is in content-type lookup
    filename = filename.lower()
    return filename[filename.rfind(".")+1:] in ext2conttype
def random_file(dir):
    #return the filename of a randomly chose image in dir
    images = [f for f in listdir(dir) ] #if isimage(f)
    #return choice(images)
    print images
def pick_file(dir):
    return null

if __name__ == "__main__":
    #dir = "../HTML/Images/"

    #dir = "/Volumes/GoogleDrive/My Drive/UnderGrad/Electrical Engineering/408_409/Git/Web-Controlled-Dog-Feeder/HTML/Images"
    #random_file(dir)
    r = os.listdir(os.path.expanduser('~/Documents/Images'))
    print r
    #r = random_file(dir)
    #print "Content-type: %s\n" % (content_type(r))
    #print file(dir+r, "rb").read()
