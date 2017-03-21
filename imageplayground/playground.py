#!/usr/bin/env python

from PIL import Image
import random


def xor_(pixel1, pixel2):
	ret = tuple(c1 ^ c2 for c1, c2 in zip(pixel1, pixel2))
	return ret

def and_(pixel1, pixel2):
	ret = tuple(c1 & c2 for c1, c2 in zip(pixel1, pixel2))
	return ret

def or_(pixel1, pixel2):
	ret = tuple(c1 | c2 for c1, c2 in zip(pixel1, pixel2))
	return ret

def sum_(pixel1, pixel2):
	ret = tuple(c1 + c2 for c1, c2 in zip(pixel1, pixel2))
	return ret

im1 = Image.open('secret.png')
width1, height1 = im1.size
im2 = Image.open('xormap.png')
width2, height2 = im2.size

im1_data = im1.load()
im2_data = im2.load()

min_width = min(width1, width2)
min_height = min(height1, height2)

max_width = max(width1, width2)
max_height = max(height1, height2)

output = Image.new('RGB', (max_width, max_height), 'white')
output_data = output.load()

for x in xrange(0, min_width):
	for y in xrange(0, min_height):
		pix1 = im1_data[x, y]
		pix2 = im2_data[x, y]
		output_data[x, y] = xor_(pix1, pix2)

output.show()
#output.save('secret.png')