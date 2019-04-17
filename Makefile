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


.SUFFIXES: 

.SUFFIXES:  .cpp .c .cu .o


.c.o:
	echo Compiling C

.cpp.o:
	echo Compiling CPP

.cu.o:
	echo Compiling NVCC

#BUILD_DIR ?= .././build
#ODIR ?= ./
#SRC_DIRS ?= ./

BUILD_DIR ?= ./build
TEST_DIR ?= ./tests
ODIR ?= ./src
SRC_DIRS ?= ./src

EXECUTABLE = solver




OBJECTS = tests_array.o tests_etarray.o main.o 




 

$(BUILD_DIR)/solver: 	$(SRC_DIRS)/main.o  \
						$(SRC_DIRS)/tests_array.o \
						$(TEST_DIR)/tests_etarray.o 
	$(NXX) 	$(SRC_DIRS)/main.cpp $(SRC_DIRS)/tests_array.cpp $(TEST_DIR)/tests_etarray.cu -o $(BUILD_DIR)/solver 






# vanilla overloaded array testing:
#$(BUILD_DIR)/tests_array.o: $(TEST_DIR)/tests_array.cpp 
#	$(NXX) -g -c $(TEST_DIR)/tests_array.cpp



# expression template testing:
#$(BUILD_DIR)/tests_etarray.o: $(TEST_DIR)/tests_etarray.cu 
#	$(NXX) -g -c $(TEST_DIR)/tests_etarray.cu

#$(SRC_DIRS)/tests_etarray.cuh



# vanilla overloaded array testing:
# $(BUILD_DIR)/tests_array.o: $(SRC_DIRS)/tests_array.cpp 
# 	$(NXX) -g -c $(SRC_DIRS)/tests_array.cpp


# # expression template testing:
# $(BUILD_DIR)/tests_etarray.o: $(SRC_DIRS)/tests_etarray.cu 
# 	$(NXX) -g -c $(SRC_DIRS)/tests_etarray.cu 





# $(BUILD_DIR)/main.o: 	$(SRC_DIRS)/main.cpp  
# 	$(NXX) -g -c $(SRC_DIRS)/main.cpp







$(OBJECTS): arrayops.hpp array_template.hpp \
			etmatrix.hpp etscalar.hpp etops1a.hpp \
			etops1.hpp etops2.hpp \
			SolverManager.hpp \
			tests_etarray.cuh \
			input.hpp geometry.hpp

.PHONY: clean


# clean: 
# 	-rm -f  \
# 			$(SRC_DIRS)/*.o  \
# 			$(BUILD_DIR)/$(EXECUTABLE)

clean: 
	-rm -f  \
			$(SRC_DIRS)/main.o  \
			$(SRC_DIRS)/geometry.o  \
			$(SRC_DIRS)/tests_array.o  \
			$(SRC_DIRS)/tests_etarray.o  \
			$(BUILD_DIR)/$(EXECUTABLE)