#!/usr/bin/python
## Jacob Holtom - parse copy/pasted gchatlogs
## Variables
import time, sys
from termcolor import colored
first = "Anya Owsenek" # First person's name in gchat
second = "1Fox" # Second person's name in gchat
## Script
filename = raw_input("What is the log file name?")
log = open(filename).read().split("\r\n")
log.pop()
blocks = []
while not (log == []):
    if log[0] == first:
        try:
            i = log.index(second)
        except ValueError:
            break
        blocks.append(log[:(i)])
        log = log[i:]
    if log[0] == second:
        try:
            i = log.index(first)
        except ValueError:
            break
        blocks.append(log[:(i)])
        log = log[i:]
for i in blocks:
    name = i.pop(0)
    if name == first:
        for x in i:
            print colored(first + ": " + x,'white')
    if name == second:
        for x in i:
            print colored(second + ": " + x,'green')

print log
