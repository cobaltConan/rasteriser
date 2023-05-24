CC=g++
INCDIRS=-I. 
OPT=-O0
CFLAGS=-Wall -Wextra -lSDL2 -g $(INCDIRS) $(OPT) 
S_Dir=src
B_Dir=build

CFILES=main.cpp objects.cpp graphics.cpp
OBJECTS=main.o objects.o graphics.o

BINARY=bin

all: $(BINARY)

$(BINARY): $(OBJECTS)
	$(CC) -o $@ $^ -lSDL2

# regular expression where % is a wildcard
%.o:/%.c
	$(CC) $(CFLAGS) -c -o $@ $^ 

clean:
	rm -rf $(BINARY) $(OBJECTS)
