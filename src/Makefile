OBJS	= main.o utility.o board.o
SOURCE	= main.cpp utility.cpp board.cpp
OUT	    = multi
CC	    = g++
FLAGS	= -g -c -std=c++17

all: $(OBJS)
		$(CC) -o $(OUT) $(OBJS)

main.o: main.cpp
		$(CC) $(FLAGS) main.cpp

utility.o: utility.cpp
		$(CC) $(FLAGS) utility.cpp

board.o: board.cpp
		$(CC) $(FLAGS) board.cpp

clean:
		rm -f $(OBJS) $(OUT)