# Compiler flags go here.
CFLAGS = -g -Wall -std=c99

# Linker flags go here.
LDFLAGS = -lm

# List of sources
SRC1 = server.c
SRC2 = client.c

# Program executable file name.
TARGET1 = server
TARGET2 = client

# Top-level rule, to compile everything.
all: $(TARGET1) $(TARGET2)

# Define all object files.
OBJ1 = $(SRC1:.c=.o)
OBJ2 = $(SRC2:.c=.o)

# Rule to link the program
$(TARGET1): $(OBJ1)
	gcc $(LDFLAGS) $^ -o $@
$(TARGET2): $(OBJ2)
	gcc $(LDFLAGS) $^ -o $@

# Compile: create object files from C source files.
%.o : %.c
	gcc $(CFLAGS) -c  $< -o $@ 

# Rule for cleaning re-compilable files.
clean:
	rm -f $(TARGET1) $(OBJ1)
	rm -f $(TARGET2) $(OBJ2)

rebuild:	clean all

.PHONY: all rebuild clean