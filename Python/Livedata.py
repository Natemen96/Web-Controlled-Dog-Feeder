import os
import tempfile
import time


val = 100

def loop (val):
	val = val - 1;

	with open('./outputFile.txt', 'w') as f:
  		f.write('%d' % val + "\n")

  	time.sleep(5)
  	if val == 0:
  		f.close()
  		return 0

  	else:
  		f.close()
  		loop(val)
loop(val)
