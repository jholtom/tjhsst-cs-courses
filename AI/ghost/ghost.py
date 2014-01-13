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

def p(c,d):
    for i in d:
        if i.startswith(c):
            return True
    return False

print "Welcome to G.H.O.S.T"
dictionary = file("dictionary.txt").read().split("\n")
dictionary.pop()
turn = 0 ## 0 is human, 1 is computer
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
        c = raw_input("Choose a letter >> ")[0]
        if c== "*":
            print "BLUFF!"
            if b(c,dictionary):
                print "Ha, You done been duped"
                break
            else:
                print "GJ, You called an infalliable AI's bluff"
                break
        word += c
        if l(word,dictionary):
            print "Loser. You spelt: " + word
            break
        print "SAFE!  The current word is: " + word
        wl = [w for w in dictionary if w.startswith(word)]
        turn = 1
    if turn == 1:
        poss = []
        for i in wl:
            if i[len(word)] not in poss:
                poss.append(i[len(word)])
        print "Possiblities: " + str(poss)
        #rand = random.randint(0,len(poss)-1)
        #word += poss[rand]
        c = raw_input("Choose a letter >> ")[0]
        word += c
        if l(word,dictionary):
            print "You actually beat the AI. You forced it to spell: " + word
            break
        print "SAFE!  The current word is: " + word
        wl = [w for w in dictionary if w.startswith(word)]
        turn = 0
