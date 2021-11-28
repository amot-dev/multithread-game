OBJS	= main.o utility.o interface.o tile.o board.o
SOURCE	= main.cpp utility.cpp interface.cpp tile.cpp board.cpp
OUT	    = multi
CC	    = g++
FLAGS	= -g -c -std=c++17

all: $(OBJS)
		$(CC) -o $(OUT) $(OBJS)

main.o: main.cpp
		$(CC) $(FLAGS) main.cpp

utility.o: utility.cpp
		$(CC) $(FLAGS) utility.cpp

interface.o: interface.cpp
		$(CC) $(FLAGS) interface.cpp

tile.o: tile.cpp
		$(CC) $(FLAGS) tile.cpp

board.o: board.cpp
		$(CC) $(FLAGS) board.cpp

clean:
		rm -f $(OBJS) $(OUT)