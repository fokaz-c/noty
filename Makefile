# Compiler and flags
CC := gcc
CFLAGS := -Wall -Wextra -std=c17

# Project structure
SRC_DIR := src
BUILD_DIR := build
INC_DIRS := $(shell find include -type d) .
INC_FLAGS := $(addprefix -I,$(INC_DIRS))

# Collect sources and object files
SRCS := $(shell find $(SRC_DIR) -name '*.c')
OBJS := $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o,$(SRCS))

# Final target
TARGET := $(BUILD_DIR)/app

# Default rule
all: $(TARGET)

# Link objects into final binary
$(TARGET): $(OBJS)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INC_FLAGS) -o $@ $^

# Compile .c -> .o
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INC_FLAGS) -c $< -o $@

# Cleanup
clean:
	rm -rf $(BUILD_DIR)

# Convenience
run: $(TARGET)
	./$(TARGET)

.PHONY: all clean run
