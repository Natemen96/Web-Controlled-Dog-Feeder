#!/usr/bin/python
import os,sys
import cgi
import cgitb; cgitb.enable()
import shutil
import matplotlib
import pylab
# set HOME environment variable to a directory the httpd server can write to
os.environ[ 'HOME' ] = '/tmp/'
# chose a non-GUI backend
matplotlib.use( 'Agg' )

#Deals with inputing data into python from the html form
form = cgi.FieldStorage()
# construct your plot
pylab.plot([1,2,3])

print "Content-Type: image/png\n"

# save the plot as a png and output directly to webserver
pylab.savefig( sys.stdout, format='png' )

def savePlot():
    pylab.savefig( "tempfile.png", format='png' )
    shutil.copyfileobj(open("tempfile.png",'rb'), sys.stdout)
