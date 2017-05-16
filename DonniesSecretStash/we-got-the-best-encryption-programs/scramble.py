#!/usr/bin/env python

# note: requires python2.7

import math
import random
import hashlib
import sys

def process(i, j):
	global DATA
	DATA[i] = chr(ord(DATA[i]) ^ j)

if len(sys.argv) < 3:
	print 'Usage: python scramble.py [file] [keyfile]'
	quit()

filename = '.'.join(sys.argv[1].split('.')[:-1])
extension = '.' + sys.argv[1].split('.')[-1]
key = open(sys.argv[2]).read().strip()
seed = int(hashlib.sha512(key).hexdigest(), 16)

random.seed(seed)

DATA = list(open(filename + extension, 'rb').read())
data_len = len(DATA)

for i in xrange(data_len):
	xor = random.randrange(255)
	process(i, xor)

outfile = ''
if extension == '.enc':
	outfile = 'decrypted-' + filename
else:
	outfile = filename + extension + '.enc'

out = open(outfile, 'wb')
out.write(''.join(DATA))
out.close()
