# Compiler settings
CC = gcc
CFLAGS = -Iinc -Wall

# Source, library, and object directories
SRC_DIR = src
INC_DIR = inc
LIB_DIR = lib
TEST_DIR = test

# Files
SRC_FILES = $(SRC_DIR)/pathfinding.c
LIB_SRC_FILES = $(wildcard $(LIB_DIR)/*/*.c)
TEST_SRC = $(wildcard $(TEST_DIR)/*.c)

OBJ_FILES = $(SRC_FILES:.c=.o) $(LIB_SRC_FILES:.c=.o) $(TEST_SRC:.c=.o)
TEST_EXEC = test_executable

# Rules
all: $(TEST_EXEC)

$(TEST_EXEC): $(OBJ_FILES)
	$(CC) $(CFLAGS) $^ -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(SRC_DIR)/*.o $(LIB_DIR)/*/*.o $(TEST_DIR)/*.o $(TEST_EXEC)
