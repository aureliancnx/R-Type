# R-Type build instructions

## Prerequisites
Make sure you have all the dependencies installed:

### Debian / Ubuntu
```console
sudo apt install build-essential cmake ninja-build
```

### MacOS
```console
brew install coreutils gcc@11 ninja cmake
```

## Build
```console
mkdir build && cd build
cmake ..
```

### Build with Ninja
Build performance is drastically better with Ninja.
```console
mkdir build && cd build
cmake -G Ninja ..
```
