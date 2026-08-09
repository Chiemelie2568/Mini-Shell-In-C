# Compiler
CC = gcc

# Compiler flags
CFLAGS = -Wall -Wextra -Wpedantic -g -Ierror_handling

# Executable
TARGET = msh

# Object files
OBJS = main.o scanner.o parser.o sys_errors.o

# Build the executable
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

# Compile main.c
main.o: src/main.c include/scanner.h include/token.h include/sys_errors.h
	$(CC) $(CFLAGS) -c main.c -o main.o

# Compile scanner.c
scanner.o: src/scanner.c include/scanner.h include/token.h include/sys_errors.h
	$(CC) $(CFLAGS) -c scanner.c -o scanner.o

# Compile parser.c
parser.o: src/parser.c include/parser.h
	$(CC) $(CFLAGS) -c src/parser.c -o parser.o

# Compile src/sys_error.c
sys_errors.o: src/sys_errors.c include/sys_errors.h
	$(CC) $(CFLAGS) -c src/sys_errors.c -o sys_errors.o

# remove .o files.
rm -f $(OBJS) $(TARGET)
