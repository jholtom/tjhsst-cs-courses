#
# Jacob Holtom - Sept 3, 2013
#
from collections import defaultdict, deque
import copy
from subprocess import Popen, PIPE
import sys
from sets import Set

#METHOD DEFINITIONS - helper stuff
def wordsearch(word_dict, source, target):
    if source == target:
        return [source]
    word_q = deque([[source]])
    visited = set([source])
    while word_q:
        neighbors = word_q.popleft()
        if neighbors[-1] == target:
            return neighbors
        adjacency = adjacent_to(word_dict, neighbors[-1])
        for adjacent in adjacency:
            if adjacent not in visited:
                visited.add(adjacent)
                n = copy.deepcopy(neighbors)
                n.append(adjacent)
                word_q.append(n)

def add_word(word_dict, word):
        for i in xrange(len(word)):
            star_word = '*'.join([word[0:i], word[i + 1:]])
            word_dict[word].append(star_word)
            word_dict[star_word].append(word)

def adjacent_to(word_dict, word):
    adjacent = []
    for star_words in word_dict[word]:
            adjacent.extend([sw for sw in word_dict[star_words] if sw != word])
    return adjacent

def words_from_file(dict_file):
        word_dict = defaultdict(list)
        with open(dict_file, 'r') as fh:
            for line in fh:
                add_word(word_dict, line.strip().lower())
        return word_dict

def word_to_pos(word,wlist):
    return wlist.index(word)  

def pos_to_word(index,wlist):
    return wlist[index]

def flood(word,connected):
    if word in connected:
        return connected
    connected.add(word)
    for i in targ[word]:
        connected=connected.union(flood(i,connected))
    return connected

def checkexistent(word,components):
    for i in components:
        if word in i:
            return True
    return False

#Abuse wc to do some idiot simple stuff for me. Get word count.
process = Popen(['wc', '-l', 'words.txt'], stdout=PIPE)
stdout, stderr = process.communicate()
wordcount = stdout
wordcount =  wordcount.split(" ")[0]
print("WordCount: " + wordcount);
#Continue to abuse external's - Get first word
process2 = Popen(['head', '-n1', 'words.txt'],stdout=PIPE)
stdout2, stderr2 = process2.communicate()
firstword = stdout2.split('\n')[0]
print('The first word is: '+ firstword)
#Yet again! - Get last word
process3 = Popen(['tail','-n1','words.txt'],stdout=PIPE)
stdout3, stderr3 = process3.communicate()
lastword = stdout3.split('\n')[0]
print ('The last word is: ' + lastword)
worddict = words_from_file('words.txt')
print "Words with max neighbors"
print "------------------------"

#Finds the maximum and prints associated words
k = [];
for i in worddict:
    if(i.find('*')!=-1): #gets rid of the starwords for the maxfinding
        pass
    else:
        k.append(len(adjacent_to(worddict,i)))
        if(k[-1] == 14):
            print i

print "Max neighbors:"
print "--------------"
print max(k)
print "Generating nbrs.txt"
#Grab clean version without starwords for the generation
wordlist = open('words.txt', 'r').read().split()
targ = []
iterate = 0
for i in wordlist:
    targ.append(adjacent_to(worddict,i))

for i in targ:
    for x in xrange(len(i)):
        i[x] = wordlist.index(i[x])
nbrs = open("nbrs.txt","w+")
count = 0
for i in targ:
    nbrs.write(str(count) + " : " + str(i) +"\n")
    count += 1
print "Done!"
largest = 0
components = []
for m in wordlist:
    connected = Set([])
    if checkexistent(word_to_pos(m,wordlist),components):
        pass
    else:
        temp = flood(word_to_pos(m,wordlist),connected)
        components.append(temp)
        if(len(temp)>largest):
            largest = len(temp)

print "Largest Component: " + str(largest)
print "Number of Connected Components: "+ str(len(components))
print "Generating size vs freq text file..."
svf = open("svf.txt","w+")
count = {}
for i in components:
    if(len(i) not in count):
        count[len(i)] = 1
    else:
        count[len(i)] += 1
for k in count:
    svf.write(str(k) + " " + str(count[k]) + "\n")

print "Generating degree vs freq text file..."
dvf = open("dvf.txt","w+")
count2 = {}
for i in targ:
    if(len(i) not in count2):
        count2[len(i)] = 1
    else:
        count2[len(i)] += 1
for k in count2:
   dvf.write(str(k) + " " + str(count2[k]) + "\n")
print "Done. Execute gnuplot on the text files"
print "Word path finder"
first = raw_input('Enter first word: ')
last = raw_input('Enter last word: ')
path = wordsearch(worddict,first,last)
if not path:
   print 'No path found for '+first+' to '+last
else:
   for w in path:
       print w
