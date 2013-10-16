import pickle
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

graph = {}
for i in nodedict:
    graph[i] = []

for i in nodedict:
    for k in edgedict:
        if i == edgedict[k][0]:
            graph[i].append((edgedict[k][1], edgedict[k][2])) 

datasave = open("datasave","w+")
pickle.dump(graph,datasave)
