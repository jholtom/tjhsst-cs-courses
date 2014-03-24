# Jacob Holtom
from math import sqrt, atan2, pi
hi = 12
l = 6
data = open('image.ppm').read().split()
w = int(data[1])
h = int(data[2])
COLORFLAG = False
def r(file1):
    nums = file1.read().split()[4:]
    file1.close()
    return nums

def c(nums):
    image = []
    for pos in range(0, len(nums), 3):
        RGB = (int(nums[pos]), int(nums[pos+1]), int(nums[pos+2]))
        image.append(int(.2 * RGB[0] + .7 * RGB[1] + .1 * RGB[2]))
    return image

def rif(name):
    imageFile = open(name, 'r')
    nums = r(imageFile)
    image = c(nums)
    return image

def s(image, passNum):
    for row in range(1, h - 1):
        for col in range(1, w - 1):
            current = row*h+col
            image[current] = (image[current]*4)+(image[current+1]*2)+(image[current-1]*2)+(image[current+w]*2)+(image[current-w]*2)+(image[current+w-1])+(image[current+w+1])+(image[current-w-1])+(image[current-w+1])
            image[current] = image[current]/16
        return image

def theta(Gx, Gy):
    return 4 * ((atan2(Gy, Gx) + (pi/8)) % pi) // pi

def sobel(image):
    newImage = [[0,0,0,0,0] for n in range(w*h)]
    for row in range(1, h - 1):
        for col in range(1, w - 1):
            current = row*h+col
            Gy = (image[current-w]-1)+2*(image[current-w])+(image[current-w]+1)-(image[current+w]-1)-2*(image[current+w])-(image[current+w]+1)
            Gy = Gy/8
            Gx = 2*(image[current+1])-2*(image[current-1])+(image[current-w+1])-(image[current-w-1])+(image[current+w+1])-(image[current+w-1])
            Gx = Gx/8
            M = sqrt(Gx**2+Gy**2)
            D = theta(Gx, Gy)
            newImage[current][0] = M
            newImage[current][1] = D
    return newImage

def fe(image):
    for row in range(1, h - 1):
        for col in range(1, w - 1):
            current = row*h+col
            if image[current][1] == 0:
                if image[current] > image[current+1] and image[current] > image[current-1]:
                    image[current][2] = 1
            if image[current][1] == 1:
                if image[current] > image[current-w+1] and image[current] > image[current+w-1]:
                    image[current][2] = 1
            if image[current][1] == 2:
                if image[current] > image[current+w] and image[current] > image[current-w]:
                    image[current][2] = 1
            if image[current][1] == 3:
                if image[current] > image[current-w-1] and image[current] > image[current+w+1]:
                    image[current][2] = 1
        return image

def etn(image):
    newImage = [0 for n in range(w*h)]
    for row in range(1, h - 1):
        for col in range(1, w - 1):
            current = row*h+col
            if image[current][2] == 1:
                newImage[current] = 255
            else:
                newImage[current] = 0
        return newImage

def fca(M, row, col):
    current = row*w+col
    if M[current][3] == 1: return
    M[current][3] = 1
    if row > 0 and M[current-w][2] == 1 and M[current-w][0] > l:
        M[current-w][3] == 1
        M[current-w][4] = 1
        fca(M, row-1, col)
    if row > 0 and M[current+w][2] == 1 and M[current+w][0] > l:
        M[current+w][3] == 1
        M[current+w][4] = 1
        fca(M, row+1, col)
    if row > 0 and M[current-1][2] == 1 and M[current-1][0] > l:
        M[current-1][3] == 1
        M[current-1][4] = 1
        fca(M, row, col-1)
    if row > 0 and M[current+1][2] == 1 and M[current+1][0] > l:
        M[current+1][3] == 1
        M[current+1][4] = 1
        fca(M, row, col+1)

def fc(image):
    for row in range(1, h - 1):
        for col in range(1, w - 1):
            current = row*h+col
            if image[current][2] == 1 and image[current][0] > hi:
                image[current][4] = 1
                fca(image, row, col)

def fn(image):
    newImage = [0 for n in range(w*h)]
    for row in range(1, h - 1):
        for col in range(1, w - 1):
            current = row*h+col
            if image[current][4] == 1 and image[current][3] == 1:
                newImage[current] = 255
            else:
                newImage[current] = 0
    return newImage


fileName = rif('image.ppm')
for smooth in range(6):
    fileName = s(fileName, smooth)
fileName = sobel(fileName)
fileName = fe(fileName)
fc(fileName)
fileName = fn(fileName)
output = open('output.ppm','w')
output.write("P3\n")
output.write("800 600\n")
output.write("255\n")
for i in fileName:
    output.write(str(i) + ' ')
output.close()
