# TLM 2019 c++ makefile
#
# build in /src
# place exe in /build
#



FXX = gfortran
CXX = g++
NXX = nvcc
CFLAGS =  -Wall #Wall: warn all unused variables  -g -O0 `sdl-config --cflags --libs`
LDFLAGS = #-lGL -lGLU -lglut -lpthread  -lSDL_mixer -lGLEW -lcuda
NVFLAGS = -g -G -O0
.SUFFIXES: .cpp .hpp .c .h .y .l .o .cu

#BUILD_DIR ?= .././build
#ODIR ?= ./
#SRC_DIRS ?= ./

BUILD_DIR ?= ./build
TEST_DIR ?= ./tests
ODIR ?= ./src
SRC_DIRS ?= ./src

EXECUTABLE = solver




OBJECTS = main.o tests_array.o tests_etarray.o




# vanilla overloaded array testing:
#$(BUILD_DIR)/tests_array.o: $(TEST_DIR)/tests_array.cpp 
#	$(NXX) -g -c $(TEST_DIR)/tests_array.cpp



# expression template testing:
#$(BUILD_DIR)/tests_etarray.o: $(TEST_DIR)/tests_etarray.cu 
#	$(NXX) -g -c $(TEST_DIR)/tests_etarray.cu


# expression template testing:
$(BUILD_DIR)/tests_etarray.o: $(SRC_DIRS)/tests_etarray.cu 
	$(NXX) -g -c $(SRC_DIRS)/tests_etarray.cu



#$(ODIR)/geometry.o  
$(BUILD_DIR)/solver: 	$(ODIR)/main.o  \
						$(ODIR)/tests_array.o \
						$(ODIR)/tests_etarray.o 
	$(NXX) -g 	$(ODIR)/main.o $(ODIR)/tests_array.o $(ODIR)/tests_etarray.o -o $(BUILD_DIR)/solver -lm



#$(BUILD_DIR)/main.o: 	$(SRC_DIRS)/main.cpp  
#	$(NXX) -g -c main.cpp











$(OBJECTS): arrayops.hpp array_template.hpp \
			etmatrix.hpp etscalar.hpp etops1a.hpp \
			etops1.hpp etops2.hpp \
			SolverManager.hpp \
			input.hpp geometry.hpp

.PHONY: clean


clean: 
	-rm -f  \
			$(SRC_DIRS)/main.o  \
			$(SRC_DIRS)/geometry.o  \
			$(SRC_DIRS)/tests_array.o  \
			$(SRC_DIRS)/tests_etarray.o  #\
			#$(BUILD_DIR)/$(EXECUTABLE)