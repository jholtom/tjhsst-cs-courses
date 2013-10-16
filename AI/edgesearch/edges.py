from collections import deque
from collections import defaultdict 
import pickle
def magic(graph,start,target):
    inf = 0
    for u in graph:
        for v ,w in graph[u]:
           inf = float(inf) + float(w)
    dist = dict([(u,inf) for u in graph])
    prev = dict([(u,None) for u in graph])
    q = graph.keys()
    dist[start] = 0
    def x(v):
        return dist[v]
    
    while q != []:
        u = min(q, key=x)
        q.remove(u)
        for v,w in graph[u]:
            alt = float(dist[u]) + float(w)
            if alt < dist[v]:
                dist[v] = alt
                prev[v] = u
    trav = []
    temp = target
    while temp != start:
        trav.append(prev[temp])
        temp = prev[temp]
    trav.reverse()
    trav.append(target)
    return " -> ".join(trav),dist[target]
datasave = open('datasave','r')
graph = pickle.load(datasave)
print magic(graph,"1701291","0600209")
