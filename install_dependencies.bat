@echo off
REM Install necessary packages using Chocolatey

choco install -y cmake
choco install -y graphviz

REM Build the project
make
