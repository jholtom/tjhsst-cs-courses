from collections import deque
from collections import defaultdict 
import pickle
import copy

def is_route(route_dict,loc):
    adjacent = []
    adjacent.extend([rw[0] for rw in route_dict[loc]])
    print adjacent 
    return adjacent

def route_search(route_dict, source, target):
    if source == target:
        return [source]
    word_q = deque([[source]])
    visited = set([source])
    while word_q:
        neighbors = word_q.pop() # POPLEFT FOR BFS / SET TO DFS NOW
        if neighbors[-1] == target:
            return neighbors
        adjacency = is_route(route_dict, neighbors[-1])
        for adjacent in adjacency:
            if adjacent not in visited:
                visited.add(adjacent)
                n = copy.deepcopy(neighbors)
                n.append(adjacent)
                word_q.append(n)


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
#print magic(graph,"1701291","0600209")
print route_search(graph,'1701291','0600209')
