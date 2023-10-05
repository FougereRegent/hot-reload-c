CC=gcc
CARGS=-g -Wall -c

bin: hot.o
	$(CC) $^ -o bin
	make clean

hot.o: hot.c
	$(CC) $(CARGS) $^

clean:
	rm -rf *.o
