COLOR_RESET := \033[0m
COLOR_RED := \033[31m
COLOR_GREEN := \033[32m
COLOR_GOLDEN := \033[33m
COLOR_BLUE := \033[34m


# List of source folders
SRC_DIRS := $(shell ls -d *)

# Compiler and flags
CXX := g++
CXXFLAGS := -Wall -Wextra -std=c++17

# Find all .cpp files in the source directories
SRC_FILES := $(wildcard $(addsuffix /*.cpp, $(SRC_DIRS)))
H_FILES := $(wildcard $(addsuffix /*.hpp, $(SRC_DIRS)))

# Define the object files
OBJ_FILES := $(patsubst %.cpp, %.o, $(SRC_FILES))

# Rule to build all object files
all: $(OBJ_FILES)
	touch .updated

# Pattern rule to compile .cpp files to .o files
%.o: %.cpp %.hpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up
clean:
	@echo "$(COLOR_RED)rm -f $(OBJ_FILES)$(COLOR_RESET)"
	@rm -f $(OBJ_FILES)
	@rm -f .updated

.PHONY: all clean
