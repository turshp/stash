#!/usr/bin/env python

'readTextFile.py -- read and display text file'

# get file name
fname = raw_input('Enter file name: ')
print

# attempt to open file for reading
try:
    fobj = open(fname, 'r')
except IOError, e:
    print '*** file open error:', e
else:
    for eachline in fobj:
        print eachline,
    fobj.close()
