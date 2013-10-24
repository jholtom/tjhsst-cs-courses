#Uniform Cost and A-Star - Jacob Holtom - 10/23/13
import heapq

def astar(self, graph, current, end, edges):
    openSet = set()
    openHeap = []
    closedSet = set()

    def retracePath(c):
        path = [c]
        while c.parent is not None:
            c = c.parent
            path.append(c)
        path.reverse()
        return path

    openSet.add(current)
    openHeap.append((0,current))
    while openSet:
        current = heapq.heappop(openHeap)[1]
        if current == end:
            return retracePath(current)
        openSet.remove(current)
        closedSet.add(current)
        for tile in graph[current]:
            if tile not in closedSet:
                #tile.H = (abs(end.x-tile.x)+abs(end.y-tile.y))*10 
                tile.H = abs(edges[(tile,end)])
                if tile not in openSet:
                    openSet.add(tile)
                    heapq.heappush(openHeap, (tile.H,tile))
                tile.parent = current
    return []

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

print astar(graph,'1701291','0600209', edges)
