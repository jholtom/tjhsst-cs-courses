# Jacob Holtom
import math
import numpy as np
data = open('image.ppm').read().split()
w = int(data[1])
h = int(data[2])
data = data[4:]
y = 0
while y < h:
    x = 0
    while x < w:
        j = 3 * (y * w + x)
        m = int((int(data[j]) * 0.30)) + int((int(data[j+1]) * 0.59)) + int((int(data[j+2]) * 0.11))
        print str(m) + ' ' + str(m) + ' ' + str(m)
        #r = data[j]
        #g = data[j+1]
        #b = data[j+2]
        x += 1
    y += 1

def gauss_kern():
   """ Returns a normalized 2D gauss kernel array for convolutions """
   h1 = w
   h2 = h
   x, y = np.mgrid[0:h2, 0:h1]
   x = x-h2/2
   y = y-h1/2
   sigma = 1.5
   g = np.exp( -( x**2 + y**2 ) / (2*sigma**2) );
   return g / g.sum()
