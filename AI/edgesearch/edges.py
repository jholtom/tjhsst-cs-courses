from collections import deque
from collections import defaultdict 
#ITS LIKE A REALLY AWESOME TO WAY TO DO THIS FAST.
class Graph:
  def __init__(self):
    self.nodes = set()
    self.edges = defaultdict(list)
    self.distances = {}
 
  def add_node(self, value):
    self.nodes.add(value)
 
  def add_edge(self, from_node, to_node, distance):
    self.edges[from_node].append(to_node)
    self.edges[to_node].append(from_node)
    self.distances[(from_node, to_node)] = distance
 
 
def dijkstra(graph, initial):
  visited = {initial: 0}
  path = {}
  nodes = set(graph.nodes)
  while nodes: 
    min_node = None
    for node in nodes:
      if node in visited:
        if min_node is None:
          min_node = node
        elif visited[node] < visited[min_node]:
          min_node = node
 
    if min_node is None:
      break
 
    nodes.remove(min_node)
    current_weight = visited[min_node]
    for edge in graph.edges[min_node]:
      weight = float(current_weight) + float(graph.distances[(min_node, edge)])
      if edge not in visited or weight < visited[edge]:
        visited[edge] = weight
        path[edge] = min_node
 
  return visited, path

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

graph = Graph()
for i in nodedict.keys():
    graph.add_node(i)

for i in edgedict:
    graph.add_edge(edgedict[i][0],edgedict[i][1],edgedict[i][2])

print dijkstra(graph,nodelist[0].split(' ')[0]) 
