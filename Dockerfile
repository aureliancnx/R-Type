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
RUN sudo apt-get install -y libtbb-dev xorg-dev libglu1-mesa-dev libxrandr-dev curl tar build-essential wget

# Add github.com to known hosts
RUN wget https://github.com/aureliancnx/R-Type/releases/latest/download/RType-Build-Linux.tar.gz

RUN tar xvf RType-Build-Linux.tar.gz
RUN mv RType-1.0.1-Linux/R-Type/* .

# Run
CMD ["./RType", "--server"]
