import random, string
from random import randint
all_words = []
def randomword(length):
   return ''.join(chr(randint(97, 122)) for i in range(length))
print(randomword(3))
f = open('u10k','w')

words1 = []
words2 = []
for i in range(10000):
	words1.append(randomword(randint(1, 20)))
	words2.append(randomword(randint(1, 20)))

words1 = list(set(words1))
#words1.sort()
for i in range(len(words1)):
	f.write(words1[i] + " " + words2[i] + "\n")


f.close() # you can omit in most cases as the destructor will call it