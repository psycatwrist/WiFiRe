
# Compiler
CC = gcc

# Executable name
TARGET = wifire

# Directories
INCLUDE_DIR = include

# Source files
SRC = src/main.c src/components/interface.c

# Object files
OBJ = $(SRC:.c=.o)

# Compiler flags
CFLAGS = -Wall -Wextra -Wpedantic -std=c11 -g

# Header search path
CPPFLAGS = -D_DEFAULT_SOURCE -I$(INCLUDE_DIR)

# libpcap flags
PCAP_CFLAGS = $(shell pkg-config --cflags libpcap)
PCAP_LIBS = $(shell pkg-config --libs libpcap)

# Default target
all: $(TARGET)

# Link object files into executable
$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(TARGET) $(PCAP_LIBS)

# Compile each source file into an object file
%.o: %.c
	$(CC) $(CPPFLAGS) $(PCAP_CFLAGS) $(CFLAGS) -c $< -o $@

# Remove generated files
clean:
	rm -f $(OBJ) $(TARGET)

.PHONY: all clean
