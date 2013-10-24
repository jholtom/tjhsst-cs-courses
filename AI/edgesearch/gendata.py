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

#ASSEMBLE GRAPH HERE
graph = {}
for i in nodedict:
        graph[i] = []

for i in nodedict:
    for k in edgedict:
        if i == edgedict[k][0]:
            graph[i].append(edgedict[k][1]) 

edges = {}
for i in edgedict:
    edges[(edgedict[i][0],edgedict[i][1])] = edgedict[i][2]

edgedump = open('edges','w+')
graphdump = open('graph','w+')
pickle.dump(graph,graphdump)
pickle.dump(edges,edgedump)
