#!/bin/env python

import numpy as np

pmtPos= np.load('pmtPos.npy')
print pmtPos[0][0]
print np.load('pmtPos.npy')
print np.load('vrt.npy')
print np.load('resFunction.npy') # load and print the C++ written NumPy array

# do the same thing from python using NumPy
#np.save('b.npy', np.linspace(0,39,40,dtype=np.float32).reshape(-1,4)) 
# load and print the python written NumPy array
#print np.load('b.npy')
