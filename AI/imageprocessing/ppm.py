# Jacob Holtom
from math import sqrt, atan2, pi
hi = 12
l = 6
data = open('image.ppm').read().split()
w = int(data[1])
h = int(data[2])
COLORFLAG = False
def readFileNumbersIntoStrings(file1):
	nums = file1.read().split()[3:]
	file1.close()
	return nums

def convertStringRGBsToGrayIntegersOrColorTuples(nums):
	image = []
	if COLORFLAG == True:
		for pos in range(0, len(nums), 3):
			RGB = (int(nums[pos]), int(nums[pos+1]), int(nums[pos+2]))
			image.append(RGB)
	else:
		for pos in range(0, len(nums), 3):
			RGB = (int(nums[pos]), int(nums[pos+1]), int(nums[pos+2]))
			image.append(int(.2 * RGB[0] + .7 * RGB[1] + .1 * RGB[2]))
	return image

def printTitleAndSizeOfImageInPixels(image):
	print('         ==<RUN TIME INFORMATION>==')
	if len(image) != w * h:
		print('--ERROR: Stated file size not equal to number of pixels')
		print('  file length:', len(image))
		print('  width:', w, 'height:', h)
		exit()
	print('--NUMBER OF PIXELS.............. ', len(image))

def readPixelColorsFromImageFile(IMAGE_FILE_NAME):
	imageFile = open(IMAGE_FILE_NAME, 'r')
	nums = readFileNumbersIntoStrings(imageFile)
	image = convertStringRGBsToGrayIntegersOrColorTuples(nums)
	printTitleAndSizeOfImageInPixels(image)
	return image

def smoothImage(image, passNum):
	for row in range(1, h - 1):
		for col in range(1, w - 1):
			current = row*h+col
			image[current] = (image[current]*4)+(image[current+1]*2)+(image[current-1]*2)+(image[current+w]*2)+(image[current-w]*2)+(image[current+w-1])+(image[current+w+1])+(image[current-w-1])+(image[current-w+1])
			image[current] = image[current]/16
	return image

def theta(Gx, Gy):
	return 4 * ((atan2(Gy, Gx) + (pi/8)) % pi) // pi

def sobelMask(image):
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

def findEdges(image):
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

def edgesToNums(image):
	newImage = [0 for n in range(w*h)]
	for row in range(1, h - 1):
		for col in range(1, w - 1):
			current = row*h+col
			if image[current][2] == 1:
				newImage[current] = 255
			else:
				newImage[current] = 0
	return newImage

def fixCellAt(M, row, col):
	current = row*w+col
	if M[current][3] == 1: return
	M[current][3] = 1
	if row > 0 and M[current-w][2] == 1 and M[current-w][0] > l:
		M[current-w][3] == 1
		M[current-w][4] = 1
		fixCellAt(M, row-1, col)

	if row > 0 and M[current+w][2] == 1 and M[current+w][0] > l:
		M[current+w][3] == 1
		M[current+w][4] = 1
		fixCellAt(M, row+1, col)

	if row > 0 and M[current-1][2] == 1 and M[current-1][0] > l:
		M[current-1][3] == 1
		M[current-1][4] = 1
		fixCellAt(M, row, col-1)

	if row > 0 and M[current+1][2] == 1 and M[current+1][0] > l:
		M[current+1][3] == 1
		M[current+1][4] = 1
		fixCellAt(M, row, col+1)

def fixCells(image):
	for row in range(1, h - 1):
		for col in range(1, w - 1):
			current = row*h+col
			if image[current][2] == 1 and image[current][0] > hi:
				image[current][4] = 1
				fixCellAt(image, row, col)

def fixedToNums(image):
	newImage = [0 for n in range(w*h)]
	for row in range(1, h - 1):
		for col in range(1, w - 1):
			current = row*h+col
			if image[current][4] == 1 and image[current][3] == 1:
				newImage[current] = 255
			else:
				newImage[current] = 0
	return newImage


fileName = readPixelColorsFromImageFile('image.ppm')
for smooth in range(6):
    fileName = smoothImage(fileName, smooth)
fileName = sobelMask(fileName)
fileName = findEdges(fileName)
fixCells(fileName)
fileName = fixedToNums(fileName)
print fileName
"""
data = open('image.ppm').read().split()
output = open('output.ppm','w')
output.write("P3")
output.write("800 600")
output.write("255")
w = int(data[1])
h = int(data[2])
data = data[4:]
output.write("255 0 0")
output.close()
"""
