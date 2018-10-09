# recInput

This script is used to generate reconstruction input in .npy format. 

# Input items
* Position of each PMT (r=19500mm): [[theta, phi]]
* Position of the vertex: [Xr, Yr, Zr]
* 28 response functions (1242 points per function): [[mean nPE]]

# Build and run
```
g++ `root-config --cflags` `root-config --libs` recInput.cc -std=c++0x -o recInput

python -c "import numpy as np ; print np.load('./tmp/pmtPos.npy') "
    ## load and print the C++ written NumPy array
```

# check output results
```
cd tmp
python check.py
```
![Output results](https://github.com/Wgoodman007/recInput/raw/master/tmp/test.png)

# References
* https://github.com/simoncblyth/np
