# Compiler and flags
CC = gcc
CFLAGS = -Wall -O2 

# Target executable
TARGET = zelda

# Source files
SOURCES = game.c inventory.c main.c mapmaker.c player.c terminal.c ucpSleep.c

# Header files
HDRS = game.h inventory.h main.h mapmaker.h player.h terminal.h ucpSleep.h

# Object files
OBJS = $(SOURCES:.c=.o)

# Additional flags (conditional compilation)
ifdef QUICK_MODE
    CFLAGS += -DQUICK_MODE
endif

# Compile each C file into its corresponding object file
%.o: %.c $(HDRS)
	$(CC) $(CFLAGS) -c $< -o $@

# Link object files into the final executable
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

# Clean up the object files and the target executable
clean:
	rm -rf $(OBJS) $(TARGET)
