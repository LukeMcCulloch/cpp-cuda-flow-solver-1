##
## http://mrbook.org/blog/tutorials/make/
##
##
## https://codereview.stackexchange.com/questions/74136/
## 	makefile-that-places-object-files-into-an-alternate-directory-bin/74139#74139
##
FXX = gfortran
CXX = g++
CFLAGS =  -Wall
LDFLAGS =

BUILD_DIR ?= ./build
SRC_DIRS ?= ./src

EXECUTABLE = solver

# target:
all: $(BUILD_DIR)/$(EXECUTABLE)

#all: $(BUILD_DIR)/main.o
#all: $(SRC_DIRS)/$(EXECUTABLE)

$(BUILD_DIR)/$(EXECUTABLE): $(SRC_DIRS)/tests_array.cpp $(SRC_DIRS)/main.cpp
	$(CXX)  $(CFLAGS) $(SRC_DIRS)/tests_array.cpp $(SRC_DIRS)/main.cpp -o $(BUILD_DIR)/$(EXECUTABLE)


#$(BUILD_DIR)/$(EXECUTABLE): $(SRC_DIRS)/main.o
#	$(CXX)  $(SRC_DIRS)/main.o -o $(BUILD_DIR)/$(EXECUTABLE)

#$(BUILD_DIR)/main.o: $(SRC_DIRS)/main.cpp
#	$(CXX)  $(BUILD_DIR)/main.o -o $(BUILD_DIR)/$(EXECUTABLE)

#$(BUILD_DIR)/main.o: $(SRC_DIRS)/main.cpp
#	$(CXX)  $(SRC_DIRS)/main.cpp -c 

# $(SRC_DIRS)/$(EXECUTABLE): $(SRC_DIRS)/main.o
# 	$(CXX)  $(SRC_DIRS)/main.o -o $(BUILD_DIR)/$(EXECUTABLE)
# $(SRC_DIRS)/main.o: $(SRC_DIRS)/main.cpp
# 	$(CXX)  $(SRC_DIRS)/main.cpp -c main.o

#./build/main.o: main.cpp
#	g++  $(SRC_DIRS)/main.cpp -o $(BUILD_DIR)/solver

.PHONY: clean


clean: 
	-rm -f  $(BUILD_DIR)/tests_array.o $(BUILD_DIR)/main.o $(BUILD_DIR)/$(EXECUTABLE)
#