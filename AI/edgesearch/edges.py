from collections import deque
from collections import defaultdict 
import pickle
import copy

def is_route(route_dict,loc):
    adjacent = []
    adjacent.extend([rw[0] for rw in route_dict[loc]])
    return adjacent

def route_search(route_dict, source, target):
    if source == target:
        return [source]
    word_q = deque([[source]])
    visited = set([source])
    while word_q:
        neighbors = word_q.popleft() # POPLEFT FOR BFS / SET TO DFS NOW POP FOR DFS
        if neighbors[-1] == target:
            return neighbors
        adjacency = is_route(route_dict, neighbors[-1])
        for adjacent in adjacency:
            if adjacent not in visited:
                visited.add(adjacent)
                n = copy.deepcopy(neighbors)
                n.append(adjacent)
                word_q.append(n)

#datasave = open('datasave','r')
#graph = pickle.load(datasave)
print route_search(graph,"1701291","0600209")
