#!/usr/bin/python
## Jacob Holtom - parse copy/pasted gchatlogs
## Variables
import time, sys
first = "Jacob Holtom" # First person's name to show up in gchat
second = "Kimbrely Holtom" # Second person's nameto show up in gchat
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
            print first + ": " + x
    if name == second:
        for x in i:
            print second + ": " + x

print log
