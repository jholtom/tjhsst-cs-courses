from collections import deque
#ITS LIKE A REALLY AWESOME TO WAY TO DO THIS FAST.
class BFS:
    def __init__(self, node,edges, source):
        self.node = node
        self.edges = edges
        self.source = source
        self.queue = deque()
        self.parent =[-1 for u in range(0,node)]
        self.construct_graph()
        self.bfs_traversal()

    def construct_graph(self):
        for u,v in self.edges:
            self.graph[u][v], self.graph[v][u] = True, True

    def bfs_traversal(self):
        self.queue.append(self.source)
        while len(self.queue):
            u =  self.queue.popleft()
            for v in range(0,self.node):
                if self.graph[u][v] == True and self.color[v]=='W':
                    self.queue.append(v)
                    self.parent[v]=u

    def print_shortest_path(self, destination):
        if destination==self.source:
            print destination,
        elif self.parent[destination] == -1:
            print "No Path"
        else:
            self.print_shortest_path(self.parent[destination])
            print "-> ",destination,

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

print nodedict
print edgedict
