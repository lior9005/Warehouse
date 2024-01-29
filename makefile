BASE_FLAGS = g++ -g -Wall -Weffc++ -std=c++11 -Iinclude

SRC_DIR = src
BIN_DIR = bin

# Get all .cpp files in the source directory
SOURCES = $(wildcard $(SRC_DIR)/*.cpp)

# Generate corresponding .o files in the bin directory
OBJECTS = $(patsubst $(SRC_DIR)/%.cpp,$(BIN_DIR)/%.o,$(SOURCES))

# Name of the final executable
EXECUTABLE = $(BIN_DIR)/warehouse

all: $(EXECUTABLE) 
	
# Linker
$(EXECUTABLE): $(OBJECTS)
	@$(BASE_FLAGS) $^ -o $@

# Creating objects from sources
$(BIN_DIR)/%.o: $(SRC_DIR)/%.cpp
	@$(BASE_FLAGS) -c $< -o $@

clean:
	rm -rf $(BIN_DIR)/*

