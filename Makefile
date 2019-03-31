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


OBJECTS = main.o tests_array.o tests_etarray.o

$(BUILD_DIR)/solver: 	$(ODIR)/main.o  \
						$(ODIR)/tests_array.o \
						$(ODIR)/tests_etarray.o 
	g++ -g 	$(ODIR)/main.o $(ODIR)/tests_array.o $(ODIR)/tests_etarray.o -o $(BUILD_DIR)/solver -lm



$(BUILD_DIR)/main.o: 	$(SRC_DIRS)/main.cpp 
	g++ -g -c main.cpp


# expression template testing:
#$(BUILD_DIR)/tests_etarray.o: $(SRC_DIRS)/tests_etarray.cpp 
#	g++ -g -c $(SRC_DIRS)/tests_etarray.cpp


# vanilla overloaded array testing:
#$(BUILD_DIR)/tests_array.o: $(SRC_DIRS)/tests_array.cpp 
#	g++ -g -c $(SRC_DIRS)/tests_array.cpp


$(OBJECTS): arrayops.hpp array_template.hpp \
			etmatrix.hpp etscalar.hpp etops1a.hpp \
			etops1.hpp etops2.hpp \
			input.hpp

.PHONY: clean


clean: 
	-rm -f  \
			$(SRC_DIRS)/main.o  \
			$(SRC_DIRS)/tests_array.o  \
			$(SRC_DIRS)/tests_etarray.o  #\
			#$(BUILD_DIR)/$(EXECUTABLE)

