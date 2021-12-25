CC = g++

CFLAGS = -D DEBUG -pthread

all: threadHello_step1 threadHelloFixed_step1_Fixed matrix_multiplication

threadHello_step1: threadHello_step1.c 
	gcc $(CFLAGS) -o threadHello_step1 threadHello_step1.c

threadHelloFixed_step1_Fixed: threadHelloFixed_step1_Fixed.c 
	gcc $(CFLAGS) -o threadHelloFixed_step1_Fixed threadHelloFixed_step1_Fixed.c 
	
matrix_multiplication: matrix_multiplication.c 
	gcc $(CFLAGS) -o matrix_multiplication matrix_multiplication.c
	
clean: 
	rm -f threadHello_step1 threadHelloFixed_step1_Fixed matrix_multiplication