#!/usr/bin/python
from termcolor import colored
who = raw_input('Get whose log?')
targ = open('/home/jholtom/.mcabber/histo/'+who,'r').read().split('\n')
for i in targ:
    if i[0:2] == "MR":
        print who.split('.')[0] +': ' + ' '.join(i.split(' ')[3:]) 
    if i[0:2] == "MS":
        print 'Jacob: ' + ' '.join(i.split(' ')[3:])
