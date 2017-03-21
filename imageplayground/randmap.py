#!/usr/bin/env python

from PIL import Image
import sys
import random

if len(sys.argv) < 3:
	print 'Usage: python randbitmap.py [width] [height]'
	quit()

width = int(sys.argv[1])
height = int(sys.argv[2])

output = Image.new('RGB', (width, height), 'black')
output_data = output.load()

random.seed(int('randomseedvalue'.encode('hex'), 16))

for x in xrange(width):
	for y in xrange(height):
		pix = tuple(random.randrange(0, 255) for _ in xrange(3))
		output_data[x, y] = pix

output.show()
output.save('xormap.png')