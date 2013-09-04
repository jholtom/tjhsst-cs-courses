#
# Jacob Holtom - Sept 3, 2013
#
#NODE CLASS FOR TREE
01
class Node:
    def __init__(self, data):
        self.left = None
        self.right = None
        self.data = data

#Open the file and read to an array
file = open("decode.txt").read().split();
#Print it
print file;
for i in file:
