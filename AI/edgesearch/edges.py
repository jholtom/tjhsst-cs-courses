##BFS and DFS CODE

if source == target:
        return [source]
    word_q = deque([[source]])
    visited = set([source])
    while word_q:
        neighbors = word_q.pop() # POPLEFT FOR BFS / SET TO DFS NOW
        if neighbors[-1] == target:
            return neighbors
        adjacency = adjacent_to(word_dict, neighbors[-1])
        for adjacent in adjacency:
            if adjacent not in visited:
                visited.add(adjacent)
                n = copy.deepcopy(neighbors)
                n.append(adjacent)
                word_q.append(n)


