# Jacob Holtom
data = open('image.ppm').read().split()
w = int(data[1])
h = int(data[2])
print w
print h
data = data[4:]

while h<1:
    while w<1:
        i = 3 * h * w
        print data[i]
    h -= 1
