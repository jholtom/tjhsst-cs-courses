#Jacob Holtom - G.H.O.S.T 12/02/13
import os, random, sys, math, string
def b(c,d):
    for i in d:
        if i.startswith(c):
            return True
    return False

def l(c,d):
    for i in d:
        if c == i and len(c) > 3:
            return True
    return False

def p(x):
    wlist = [w for w in dictionary if w.startswith(x)]
    poss = []
    for i in wlist:
        if i[len(word)] not in poss:
            poss.append(i[len(word)])
    return poss
def check(word,poss,dictionary):
    if l(word,dictionary):
        if len(word) % 2 == 0:
            print "Player 1 will win with: " + word
        if len(word) % 2 == 1:
            print "Player 2 will win with: " + word
    wlist = [w for w in dictionary if w.startswith(word)]
    for i in poss:
        print "checking " + i    
        wlist = [w for w in dictionary if w.startswith(word+i)]
        if wlist == []:
            for i in wlist:
                check(i,p(i),dictionary)

print "Welcome to G.H.O.S.T"
dictionary = file("dictionary.txt").read().split("\n")
dictionary.pop()
turn = 0 ## 0 is player 1, 1 is player 2
word = ""
wl = []
while True:
    if turn == 0:
        if len(word) != 0:
            print "Current word is: " + word
        poss = []
        for i in wl:
            if i[len(word)] not in poss:
                poss.append(i[len(word)])
        print "Possiblities: " + str(poss)
        c = raw_input("Player 1: Choose a letter >> ")[0]
        if c== "*":
            print "BLUFF!"
            if b(c,dictionary):
                print "Ha, You done been duped"
                break
            else:
                print "GJ, You called out the liar."
                break
        word += c
        if l(word,dictionary):
            print "Loser. You spelt: " + word
            break
        print "SAFE!  The current word is: " + word
        wl = [w for w in dictionary if w.startswith(word)]
        turn = 1
    if turn == 1:
        if len(word) != 0:
            print "Current word is: " + word
        poss = []
        for i in wl:
            if i[len(word)] not in poss:
                poss.append(i[len(word)])
        print "Possiblities: " + str(poss)
        c = raw_input("Player 1: Choose a letter >> ")[0]
        if c== "*":
            print "BLUFF!"
            if b(c,dictionary):
                print "Ha, You done been duped"
                break
            else:
                print "GJ, You called out the liar."
                break
        word += c
        if l(word,dictionary):
            print "Loser. You spelt: " + word
            break
        print "SAFE!  The current word is: " + word
        wl = [w for w in dictionary if w.startswith(word)]
        turn = 0
