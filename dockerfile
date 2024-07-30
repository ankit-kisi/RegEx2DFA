# Use the official Ubuntu base image
FROM ubuntu:latest

# Install dependencies
RUN apt-get update && \
    apt-get install -y build-essential cmake pkg-config libgvc-dev

# Set the working directory inside the container
WORKDIR /usr/src/app

# Copy the entire project into the container
COPY . .

# Create a build directory
RUN mkdir build

# Set the working directory to the build directory
WORKDIR /usr/src/app/build

# Run CMake to configure the project
RUN cmake ..

# Build the project
RUN cmake --build .

# Set the command to run your application
CMD ["./RegEx2DFA"]
