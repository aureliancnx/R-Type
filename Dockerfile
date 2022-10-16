# Using latest epitech docker image as a reference
FROM ubuntu:latest

# Set workdir to folder /app
WORKDIR /app

# Copy source code
COPY . .

# Update package updater
RUN apt-get update -y

# Install needed packages
RUN apt-get install sudo -y
RUN sudo apt-get install -y ninja-build gcc g++ cmake libtbb-dev xorg-dev libglu1-mesa-dev libxrandr-dev curl zip unzip tar git build-essential

# Check ninja version
RUN ninja --version

# Install vcpkg
#RUN git clone https://github.com/Microsoft/vcpkg.git
#RUN ./vcpkg/bootstrap-vcpkg.sh
#RUN ./vcpkg/vcpkg integrate install

ENV CXX "g++"

# Build
RUN rm -rf build/
RUN mkdir build
RUN cmake -S . -B build; true
RUN cmake --build build --config Debug
#-DCMAKE_TOOLCHAIN_FILE=/app/vcpkg/scripts/buildsystems/vcpkg.cmake

# Run
CMD ["./RType", "--server"]
