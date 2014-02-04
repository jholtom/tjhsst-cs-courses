# Jacob Holtom
data = open('image.ppm').read().split()
w = int(data[1])
h = int(data[2])
data = data[4:]
y = 0
while y < h:
    x = 0
    while x < w:
        j = 3 * (y * w + x)
        print str(int((int(data[j]) * 0.30))) + ' ' +  str(int((int(data[j+1]) * 0.59))) + ' ' + str(int((int(data[j+2]) * 0.11)))
        x += 1
    y += 1
