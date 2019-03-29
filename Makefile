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
						$(ODIR)/tests_array.o \
						$(ODIR)/tests_etarray.o 
	g++ -g 	$(ODIR)/main.o $(ODIR)/tests_array.o $(ODIR)/tests_etarray.o -o $(BUILD_DIR)/solver -lm



$(BUILD_DIR)/main.o: 	$(SRC_DIRS)main.cpp \
						$(SRC_DIRS)array_template.hpp \
						$(SRC_DIRS)SolverManager.hpp \
						$(SRC_DIRS)input.hpp \
						$(SRC_DIRS)tests_array.hpp \
						$(SRC_DIRS)tests_etarray.hpp 
	g++ -g -c main.cpp



$(BUILD_DIR)/tests_etarray.o: $(SRC_DIRS)/tests_etarray.cpp \
							$(SRC_DIRS)/etops.hpp \
							$(SRC_DIRS)/etscalar.hpp \
							$(SRC_DIRS)/etmatrix.hpp \
							$(SRC_DIRS)/array_template.hpp
	g++ -g -c $(SRC_DIRS)/tests_etarray.cpp

	
$(BUILD_DIR)/tests_array.o: $(SRC_DIRS)/tests_array.cpp \
							$(SRC_DIRS)/array_template.hpp
	g++ -g -c $(SRC_DIRS)/tests_array.cpp



.PHONY: clean


clean: 
	-rm -f  \
			$(SRC_DIRS)/main.o  \
			$(SRC_DIRS)/tests_array.o  \
			$(SRC_DIRS)/tests_etarray.o  #\
			#$(BUILD_DIR)/$(EXECUTABLE)