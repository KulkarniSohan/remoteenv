CC := g++
CFLAGS := -std=c++0x -g
#CFLAGS := -std=c++11 -g3
EXE := niyujClient
BUILD := ./build
OBJ_DIR := $(BUILD)/objects
APP_DIR := ./bin
INC := -I ./src/ 
LD_FLAGS := -lpthread
SRC := $(shell find ./src/ -type f -name '*.cpp')
OBJECTS := $(SRC:%.cpp=$(OBJ_DIR)/%.o)

all: build $(APP_DIR)/$(EXE)


$(OBJ_DIR)/%.o: %.cpp
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(INC) -c $< -o $@ $(LD_FLAGS)

$(APP_DIR)/$(EXE): $(OBJECTS)
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -o $(APP_DIR)/$(EXE) $^ $(LD_FLAGS)

build:
	@mkdir -p $(APP_DIR)
	@mkdir -p $(OBJ_DIR)

clean:
	-@rm -rvf $(OBJ_DIR)/*
	-@rm -rvf $(APP_DIR)/*

