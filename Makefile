# Variables
BUILD_DIR = build
CMAKE_FLAGS = ..

# Default target
all: build

build:
	mkdir -p $(BUILD_DIR)
	cd $(BUILD_DIR) && cmake $(CMAKE_FLAGS)
	cd $(BUILD_DIR) && make

clean:
	rm -rf $(BUILD_DIR)

.PHONY: all build clean
