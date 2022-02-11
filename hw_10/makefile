all: main.o address.o
	gcc -o program main.o address.o

main.o: main.c address.h
	gcc -c main.c

address.o: address.c address.h
	gcc -c address.c

run:
	./program
	
clean:
	rm *.o
