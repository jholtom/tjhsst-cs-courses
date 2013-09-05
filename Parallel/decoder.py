# Jacob Holtom - Sept 3, 2013
def decode(msg,encoding):
    i = msg[:1]
    k = 1
    if msg == "":
        return;
    while(("1" + i) not in encoding.keys()):
        i += msg[k:k+1]
        k += 1
    print encoding["1" + i],
    decode(msg[len(i):],encoding)
file = open("decode.txt").read().split("\r\n");
file.pop()
message = file.pop()
matrix = {}
for i in file:
    matrix[str(int("1"+i[1:]))] = i[:1]
decode(message,matrix)
