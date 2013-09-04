#
# Jacob Holtom - Sept 3, 2013
#
from collections import defaultdict, deque
from optparse import OptionParser
import copy
from subprocess import Popen, PIPE
import sys

#METHOD DEFINITIONS - helper stuff
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
