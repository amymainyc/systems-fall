all: main.o worker.o
	gcc -o main main.o
	gcc -o worker worker.o

main.o: main.c
	gcc -c main.c

worker.o: worker.c
	gcc -c worker.c

clean:
	rm *.o
	rm main
	rm worker