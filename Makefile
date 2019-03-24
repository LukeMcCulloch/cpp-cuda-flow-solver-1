##
## http://mrbook.org/blog/tutorials/make/
##

BUILD_DIR ?= ./build
SRC_DIRS ?= ./src




#solver_experiments  makefile

./build/test: 
	g++  $(SRC_DIRS)/main.cpp -o $(BUILD_DIR)/solver



.PHONY: clean


clean: 
	-rm -f  $(BUILD_DIR)/main.o
#