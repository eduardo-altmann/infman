# Compiler and flags
CC = gcc
CFLAGS = -Wall -Iinclude -O2

# Directories
SRC_DIR = src
INCLUDE_DIR = include
ASSETS_DIR = assets
BUILD_DIR = build

# Files
SRC_FILES = $(wildcard $(SRC_DIR)/*.c)
OBJ_FILES = $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(SRC_FILES))
TARGET = $(BUILD_DIR)/game

# Default target
all: $(TARGET)

# Build target
$(TARGET): $(OBJ_FILES) | $(BUILD_DIR)
	$(CC) $(OBJ_FILES) -o $@ -lraylib -lm

# Object files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Create build directory if it doesn't exist
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Run the program
run: all
	./$(TARGET)

# Clean build artifacts
clean:
	rm -rf $(BUILD_DIR)

.PHONY: all clean run
