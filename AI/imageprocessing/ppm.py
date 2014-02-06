# Jacob Holtom
import math
data = open('image.ppm').read().split()
w = int(data[1])
h = int(data[2])
data = data[4:]
y = 0
while y < h:
    x = 0
    while x < w:
        j = 3 * (y * w + x)
        #print str(int((int(data[j]) * 0.30))) + ' ' +  str(int((int(data[j+1]) * 0.59))) + ' ' + str(int((int(data[j+2]) * 0.11)))
        r = data[j]
        g = data[j+1]
        b = data[j+2]
        x += 1
    y += 1

def blur(x,y,omega):
    """Applies Gaussian Function to x and y based on omega"""
    g = (1 / (2*math.pi*(omega ** 2))) * math.e ** ( -1 * (((x ** 2) + (y ** 2)) / ( 2 * (omega ** 2))))
    return g
