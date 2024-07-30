#!/bin/bash

# Update and install necessary packages
sudo apt-get update
sudo apt-get install -y \
    build-essential \
    cmake \
    graphviz \
    libgraphviz-dev

# Build the project
make
