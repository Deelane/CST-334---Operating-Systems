CC = g++

CFLAGS = -D DEBUG

all: step1 step2 step3

step1: step1.c 
	gcc $(CFLAGS) -o step1 step1.c

step2: step2.c 
	gcc $(CFLAGS) -o step2 step2.c

step3: step3.c 
	gcc $(CFLAGS) -o step3 step3.c
	
clean: 
	rm -f step1 step2 step3