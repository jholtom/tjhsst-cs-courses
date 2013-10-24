#Uniform Cost and A-Star - Jacob Holtom - 10/23/13
import heapq
import pickle
import pu.db

def astar(graph, current, end, edges):
    openSet = set()
    openHeap = []
    closedSet = set()
    parents = {}
    def retracePath(c):
        path = [c]
        while parents[c] is not None:
            c = parents[c]
            path.append(c)
        path.reverse()
        return path

    openSet.add(current)
    openHeap.append((0,current))
    pu.db
    while openSet:
        current = heapq.heappop(openHeap)[1]
        if current == end:
            return retracePath(current)
        openSet.remove(current)
        closedSet.add(current)
        for loc in graph[current]:
            if loc not in closedSet:
                temp = abs(float(edges[(current,loc)]))
                if loc not in openSet:
                    openSet.add(loc)
                    heapq.heappush(openHeap, (temp,loc))
                parents[loc] = current
    return []

graph = pickle.load(open('graph','r'))
edges = pickle.load(open('edges','r'))
print astar(graph,'1701291','0600209', edges)
