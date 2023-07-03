CC=gcc
AR=ar
FLAGS= -Wall -g


all: libmy_mat.a  connections
 
connections :  main.o libmy_mat.a
	$(CC) $(FLAGS) -o connections main.o libmy_mat.a

my_mat.o: my_mat.c my_mat.h
	$(CC) $(FLAGS) -c my_mat.c


libmy_mat.a: my_mat.o 
	$(AR) -rcs libmy_mat.a my_mat.o 

main.o: main.c my_mat.h
	$(CC) $(FLAGS) -c main.c

clean:
	rm -f *.o *.a connections

.PHONY: clean all