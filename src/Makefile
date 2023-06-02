#CC = g++
LOADLIBES = -lSDL2
CXXFLAGS = -Wall -O0 -g


SRC1 = objects.cpp graphics.cpp

SRC2 = main.cpp

SRC  = $(SRC1) $(SRC2)

OBJS = $(SRC1:.cpp=.o)

AUX = $(SRC1:.c=.h)

main: $(OBJS) $(SRC2)
#   Built by implicit rules

.PHONY: clean
clean:
	rm -f *.o main
