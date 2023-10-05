CARGS=-g -Wall -c
CC=gcc

libmain.so: main.o
	$(CC) -shared -o libmain.so $^
	make clean_obj

main.o: main.c
	$(CC) $(CARGS) $^

clean_obj:
	rm -f *.o
