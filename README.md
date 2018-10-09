# recInput

This script is used to generate reconstruction input in .npy format. 

# Input items
* Position of each PMT: (PMTx, PMTy, PMTz)
* Position of the vertex: (Xr, Yr, Zr)
* 29 response functions: (theta, mean nPE)
* energy scale: one constant

# Build and run
g++ recInput.cc -std=c++0x -o recInput

# References
* https://github.com/simoncblyth/np
