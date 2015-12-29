# Compiler flags go here.
CFLAGS = -g -Wall -std=c99

# Linker flags go here.
LDFLAGS = -lm

# List of sources
SRC = database.c

# Program executable file name.
TARGET = run

# Top-level rule, to compile everything.
all: $(TARGET)

# Define all object files.
OBJ = $(SRC:.c=.o)

# Rule to link the program, last part is important for mySQL
$(TARGET): $(OBJ)
	gcc $(LDFLAGS) $^ -o $@ `mysql_config --cflags --libs`

# Compile: create object files from C source files.
%.o : %.c
	gcc $(CFLAGS) -c  $< -o $@

# Rule for cleaning re-compilable files.
clean:
	rm -f $(TARGET) $(OBJ)

rebuild:	clean all

.PHONY: all rebuild clean