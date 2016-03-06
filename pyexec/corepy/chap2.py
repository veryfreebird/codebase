#!/usr/bin/env python
import sys
"this is a comment"
#this is another comment

myString = 'this is a test'
print myString
print "%s is number %d" % ('python', 1)
print >> sys.stderr, 'Fata error happened'

logfile = open('logfile.txt','a')
print >> logfile, 'log to file'
logfile.close()

#user = raw_input('Enter login name:')
#print 'login name is:',user

#num = raw_input('Enter a number:')
#print 'doubling your number is %d' % (int(num)*2)

print 2<3<4<4.1<5
print 2<3<2

print 2<3 and 4<5
print 2<3 and 4>5

print '%f' % (32//3)

print 1+2*4
