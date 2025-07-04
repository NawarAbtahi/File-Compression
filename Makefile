# Compiler
CC = gcc

# Directories
SRC_DIR = src

# Source files
SRC = $(SRC_DIR)/main.c $(SRC_DIR)/rle.c

# Output binary
OUT = main

# Build rule
all: $(OUT)

$(OUT): $(SRC)
	$(CC) -o $(OUT) $(SRC)

# Run the compiled program
run: $(OUT)
	./$(OUT)

# Clean up
clean:
	rm -f $(OUT)

