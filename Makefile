##
## http://mrbook.org/blog/tutorials/make/
##

BUILD_DIR ?= ./build
SRC_DIRS ?= ./src




#solver_experiments  makefile

./build/test: 
	g++  ./src/main.cpp -o $(BUILD_DIR)/solver



.PHONY: clean


clean: 
	-rm -f  driver #./build/main.o
#