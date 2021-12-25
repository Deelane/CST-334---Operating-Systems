CC = g++

CFLAGS = -D DEBUG -pthread

all: step2 

step2: step2.c 
	gcc $(CFLAGS) -o step2 step2.c
	
clean: 
	rm -f step2 