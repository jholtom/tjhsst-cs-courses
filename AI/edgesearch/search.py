#Uniform Cost and A-Star - Jacob Holtom - 10/23/13
import heapq
import pickle

def astar(graph, current, end, edges):
    openSet = set()
    openHeap = []
    closedSet = set()
    parents = {}
    parents[current] = None
    def retracePath(c):
        path = [c]
        while parents[c] is not None:
            c = parents[c]
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
        #print 'Searching for paths from '+current
        for loc in graph[current]:
            if loc not in closedSet:
                temp = abs(float(edges[frozenset([current,loc])]))
                if loc not in openSet:
                    openSet.add(loc)
                    heapq.heappush(openHeap, (temp,loc))
                parents[loc] = current
                #print '\t'+loc
    return []

graph = pickle.load(open('graph','r'))
edges = pickle.load(open('edges','r'))
print "RECOMMENDED: 1701291 to 0600209"
print "RECOMMENDED: 2900190 to 2900275"
start = raw_input('Starting node?') 
end = raw_input('Ending node?')
path = astar(graph, start, end, edges)
print "Path Length: " + str(len(path))
for i in path:
    print i,' -> ',
