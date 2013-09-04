#
# Jacob Holtom - Sept 3, 2013
#
from subprocess import Popen, PIPE
import sys
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
