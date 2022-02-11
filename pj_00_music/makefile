all: main.o playlist.o library.o
	gcc -o program main.o playlist.o library.o

main.o: main.c playlist.h library.h
	gcc -c main.c

playlist.o: playlist.c playlist.h
	gcc -c playlist.c

library.o: library.c library.h
	gcc -c library.c

run:
	./program
	
clean:
	rm *.o
