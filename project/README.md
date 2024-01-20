# SFML + TGUI with vcpkg

## Install dependencies
Setup vcpkg according to the manual.

Example for windows 64 bit
```
## !!!Important!!!
# Checkout to the older version where 0.9.5 TGUI is present
# make sure that you are not using version 1 and above, there are some complications with SFML backend
git checkout b5efc3901285b351b85f7701ea19d082e4ec2524
./vcpkg.exe install --triplet=x64-windows tgui sfml
```

Then run cmake command for example like this from `build` dir:
```
cmake .. -DCMAKE_TOOLCHAIN_FILE=~/source/repos/vcpkg/scripts/buildsystems/vcpkg.cmake
```


## Common workflow to build project
Go to project root (root cmakefile list)
```
mkdir build && cd build
cmake .. -DCMAKE_TOOLCHAIN_FILE=~/source/repos/vcpkg/scripts/buildsystems/vcpkg.cmake
# build your project
```