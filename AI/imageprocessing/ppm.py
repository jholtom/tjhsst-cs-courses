# Jacob Holtom
data = open('image.ppm').read().split()
w = int(data[1])
h = int(data[2])
print w
print h
data = data[4:]

y = 0
while y < h:
    x = 0
    while x < w:
        j = 3 * (y * w + x)
        x += 1
    y += 1
