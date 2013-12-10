#!/usr/bin/python
from termcolor import colored
who = raw_input('Get whose log?')
targ = open('/home/jholtom/.mcabber/histo/'+who,'r').read().split('\n')
for i in targ:
    if i[0:2] == "MR":
        print colored(who.split('.')[0] +': ','white') + colored(' '.join(i.split(' ')[3:]),'white') 
    if i[0:2] == "MS":
        print colored('Jacob: ','green') + colored(' '.join(i.split(' ')[3:]),'green')
