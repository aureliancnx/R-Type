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
git submodule update --init --recursive
mkdir build && cd build
```

### Build Client
```console
cmake -G Ninja -DIS_SERVER:BOOLEAN=FALSE ..
```

### Build Server
```console
cmake -G Ninja -DIS_SERVER:BOOLEAN=TRUE ..
```