#!/usr/bin/python
from termcolor import colored
name = raw_input('what irc log? ')
who = raw_input('irc username? ')
f = open(name,'r').read().split('\n')
for i in f:
    if who in i:
        print colored(i,'white')
    if "jholtom" in i:
        print colored(i,'green')
