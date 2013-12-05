#Jacob Holtom - G.H.O.S.T 12/02/13
dictionary = file("dictionary.txt").read().split("\n")
def isWord(a):
    if a in dictionary:
        return False
    return True
print "Welcome to G.H.O.S.T"
a = raw_input("Enter a letter: ")
turn0 = 0
turn1 = 0
while not isWord(a):
    if turn0 == 1:
        a = raw_input("Enter a letter: ")
    if turn1 == 1:
        a = raw_input("Enter a letter: ")

