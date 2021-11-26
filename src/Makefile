OBJS	= main.o board.o
SOURCE	= main.cpp board.cpp
OUT	    = multi
CC	    = g++
FLAGS	= -g -c -std=c++17

all: $(OBJS)
		$(CC) -o $(OUT) $(OBJS)

main.o: main.cpp
		$(CC) $(FLAGS) main.cpp

board.o: board.cpp
		$(CC) $(FLAGS) board.cpp

clean:
		rm -f $(OBJS) $(OUT)