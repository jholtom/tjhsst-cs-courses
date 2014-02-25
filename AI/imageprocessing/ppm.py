# Jacob Holtom
import math
import numpy as np

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

data = open('image.ppm').read().split()
output = open('output.ppm','w')
#Write PPM header
output.write("P3")
output.write("800 600")
output.write("255")
w = int(data[1])
h = int(data[2])
data = data[4:]
y = 0
array = [[0 for x in xrange(h)] for x in xrange(w)]
gauss = gauss_kern()
while y < h:
    x = 0
    while x < w:
        j = 3 * (y * w + x)
        m = int((int(data[j]) * 0.30)) + int((int(data[j+1]) * 0.59)) + int((int(data[j+2]) * 0.11))
        array[x][y] = m
        output.write(str(array[x][y]) + ' ' + str(array[x][y]) + ' ' + str(array[x][y]))
        gx = 1.0 #
        gy = 1.0 #gaussian function here.
        theta = math.atan2(gy,gx)
        thatoneg = abs(gx) + abs(gy)
        if thatoneg > 100:
             if thatoneg > gauss[m]:
                 output.write("255 0 0")
        x += 1
    y += 1

output.close()
