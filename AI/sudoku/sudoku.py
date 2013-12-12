#Jacob Holtom - 11/27/13
import sys
def nrow(i,j): return (i/9 == j/9)
def ncol(i,j): return (i-j) % 9 == 0
def nblock(i,j): return (i/27 == j/27 and i%9/3 == j%9/3)

def r(a):
  global count
  i = a.find('.')
  if i == -1:
    print "solved with backtrack count: " + str(count)
    sys.exit()
  
  ignores = set()
  for j in range(81):
    if nrow(i,j) or ncol(i,j) or nblock(i,j):
      count += 1
      ignores.add(a[j])

  for m in '123456789':
    if m not in ignores:
      r(a[:i]+m+a[i+1:])
      
filename = raw_input('What file to solve? ')
puzzles = file(filename).read().strip().split("\n")
for i in puzzles:
  print "Solving: "+i
  count = 0
  r(i)
