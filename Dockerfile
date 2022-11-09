# Using latest epitech docker image as a reference
FROM ubuntu:latest

# Expose ports
EXPOSE 7777/tcp
EXPOSE 7777/udp

# Set workdir to folder /app
WORKDIR /app

# Update package updater
RUN apt-get update -y

# Install needed packages
RUN apt-get install sudo -y
RUN sudo apt-get install -y ninja-build gcc g++ cmake libtbb-dev xorg-dev libglu1-mesa-dev libxrandr-dev curl zip unzip tar git build-essential

# Check ninja version
RUN ninja --version

# Download last version of the repository
RUN git clone git@github.com:aureliancnx/R-Type.git .
RUN cd R-Type
RUN git submodule update --init --recursive

ENV CXX "g++"

# Build
RUN rm -rf build/; rm -rf cmake-build-debug/; rm -rf out/
RUN rm -rf .git
RUN rm -rf
RUN mkdir build
RUN cmake -S . -B build -G Ninja
RUN cmake --build build --config Debug -G Ninja

# Run
CMD ["./build/RType", "--server"]
