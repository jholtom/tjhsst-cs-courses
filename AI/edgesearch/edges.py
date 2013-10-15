from collections import deque
#ITS LIKE A REALLY AWESOME TO WAY TO DO THIS FAST.
nodefile = open('nodes.txt','r')
edgefile = open('edges.txt','r')
nodelist = list(nodefile)
edgelist = list(edgefile)
nodedict = {}
edgedict = {}
for i in range(len(nodelist)):
    nodedict[nodelist[i].split(' ')[0]] = [nodelist[i].split(' ')[1],nodelist[i].split(' ')[2].split('\n')[0]]

for i in range(len(edgelist)):
    edgedict[edgelist[i].split(' ')[0]] = [edgelist[i].split(' ')[1],edgelist[i].split(' ')[2],edgelist[i].split(' ')[3].split('\n')[0]]

edges = []
for i in range(len(edgelist)):
    edges.append((edgelist[i].split(' ')[1],edgelist[i].split(' ')[2]))

