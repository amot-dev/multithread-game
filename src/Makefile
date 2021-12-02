OBJS	= main.o utility.o interface.o board.o tile.o
SOURCE	= main.cpp utility.cpp interface.cpp board.cpp tile.cpp
OUT	    = multi
CC	    = g++
FLAGS	= -g -c -std=c++17

all: $(OBJS)
		$(CC) -o $(OUT) $(OBJS)

test:
		#build test file
		./test

clean:
		rm -f $(OBJS) $(OUT)

main.o: main.cpp
		$(CC) $(FLAGS) main.cpp

utility.o: utility.cpp
		$(CC) $(FLAGS) utility.cpp

interface.o: interface.cpp
		$(CC) $(FLAGS) interface.cpp

board.o: board.cpp
		$(CC) $(FLAGS) board.cpp

tile.o: tile.cpp
		$(CC) $(FLAGS) tile.cpp