OBJS	= main.o
SOURCE	= main.cpp
OUT	    = multi
CC	    = g++
FLAGS	= -g -c 

all: $(OBJS)
		$(CC) -o $(OUT) $(OBJS)

main.o: main.cpp
		$(CC) $(FLAGS) main.cpp

clean:
		rm -f $(OBJS) $(OUT)