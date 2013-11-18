import time, random
def cross(A, B):
    return [a+b for a in A for b in B]

digits   = '123456789'
rows     = 'ABCDEFGHI'
cols     = digits
squares  = cross(rows, cols)
unitlist = ([cross(rows, c) for c in cols] +
            [cross(r, cols) for r in rows] +
            [cross(rs, cs) for rs in ('ABC','DEF','GHI') for cs in ('123','456','789')])
units = dict((s, [u for u in unitlist if s in u])
             for s in squares)
peers = dict((s, set(sum(units[s],[]))-set([s]))
             for s in squares)

def assign(values, s, d):
    other_values = values[s].replace(d, '')
    if all(elim(values, s, d2) for d2 in other_values):
        return values
    else:
        return False

def elim(values, s, d):
    if d not in values[s]:
        return values
    values[s] = values[s].replace(d,'')
    if len(values[s]) == 0:
        return False
    elif len(values[s]) == 1:
        d2 = values[s]
        if not all(elim(values, s2, d2) for s2 in peers[s]):
            return False
    for u in units[s]:
        dplaces = [s for s in u if d in values[s]]
        if len(dplaces) == 0:
            return False
        elif len(dplaces) == 1:
            if not assign(values, dplaces[0], d):
                return False
    return values

def solve(grid): 
    values = dict((s, digits) for s in squares)
    chars = [c for c in grid if c in digits or c in '.']
    stor = dict(zip(squares, chars))
    for s,d in stor.items():
        if d in digits and not assign(values, s, d):
            return False
    return search(values)

def search(values):
    if values is False:
        return False
    if all(len(values[s]) == 1 for s in squares):
        return values
    n,s = min((len(values[s]), s) for s in squares if len(values[s]) > 1)
    return s(search(assign(values.copy(), s, d) for d in values[s]))

def s(seq):
    for i in seq:
        if i: return i
    return False

def sa(grids):
    def sl(grid):
        values = solve(grid)
        return solved(values)
    results = [sl(grid) for grid in grids]
    N = len(grids)
    if N > 1:
        print "Solved %d out of %d puzzles" % (
            sum(results), N)

def solved(values):
    def us(unit): return set(values[s] for s in unit) == set(digits)
    return values is not False and all(us(unit) for unit in unitlist)

filename = raw_input('What file to solve? ')
sa(file(filename).read().strip().split("\n"))
