#Jacob Holtom - 11/27/13

import sys

def same_row(i,j): return (i/9 == j/9)
def same_col(i,j): return (i-j) % 9 == 0
def same_block(i,j): return (i/27 == j/27 and i%9/3 == j%9/3)

def r(a):
  i = a.find('.')
  if i == -1:
    sys.exit(a)

  excluded_numbers = set()
  for j in range(81):
    if same_row(i,j) or same_col(i,j) or same_block(i,j):
      excluded_numbers.add(a[j])

  for m in '123456789':
    if m not in excluded_numbers:
      r(a[:i]+m+a[i+1:])
      
filename = raw_input('What file to solve? ')
puzzles = file(filename).read().strip().split("\n")
for i in puzzles:
  r(i)
