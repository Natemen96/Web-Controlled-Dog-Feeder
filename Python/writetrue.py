#!/usr/bin/python
# Write 1 to text file and redirect back to homepage
import cgi, cgitb
cgitb.enable()

import os
import tempfile

print 'Content-Type: text/html\n\n'
print ()


val = 1

with open('./feedme.txt', 'w+') as f:
	f.write('%d' % val )

#print # HTTP says you have to have a blank line between headers and content

print '<html>'
print '  <head>'
print '    <meta http-equiv="refresh" content="0;url=http://localhost/~nathanmensah/Web-Controlled-Dog-Feeder/HTML/index.html" />'
print '    <title>You are going to be redirected</title>'
print '  </head>'
print '  <body>'
print '    Redirecting...'
print '  </body>'
print '</html>'
