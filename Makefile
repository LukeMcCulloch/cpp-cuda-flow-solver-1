# TLM 2019 c++ makefile
#
# build in /src
# place exe in /build
#

FXX = gfortran
CXX = g++
CFLAGS =  -Wall #Wall: warn all unused variables
LDFLAGS =

#BUILD_DIR ?= .././build
#ODIR ?= ./
#SRC_DIRS ?= ./

BUILD_DIR ?= ./build
ODIR ?= ./src
SRC_DIRS ?= ./src

EXECUTABLE = solver


$(BUILD_DIR)/solver: 	$(ODIR)/main.o  \
						$(ODIR)/tests_array.o 
	g++ -g 	$(ODIR)/main.o $(ODIR)/tests_array.o -o $(BUILD_DIR)/solver -lm



$(BUILD_DIR)/main.o: 	$(SRC_DIRS)main.cpp \
						$(SRC_DIRS)array_template.hpp \
						$(SRC_DIRS)SolverManager.hpp \
						$(SRC_DIRS)input.hpp \
						$(SRC_DIRS)tests_array.hpp
	g++ -g -c main.cpp



$(BUILD_DIR)/tests_array.o: $(SRC_DIRS)/tests_array.cpp \
							$(SRC_DIRS)/array_template.hpp
	g++ -g -c $(SRC_DIRS)/tests_array.cpp



.PHONY: clean


clean: 
	-rm -f  \
			$(SRC_DIRS)/main.o  \
			$(SRC_DIRS)/tests_array.o  #\
			#$(BUILD_DIR)/$(EXECUTABLE)