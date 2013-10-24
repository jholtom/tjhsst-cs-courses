#Uniform Cost and A-Star - Jacob Holtom - 10/23/13
import heapq

def astar(graph, current, end, edges):
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

graph = pickle.load(open('graph','r'))
edges = pickle.load(open('edges','r'))
print astar(graph,'1701291','0600209', edges)
