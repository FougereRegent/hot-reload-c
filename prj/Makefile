CARGS=-g -Wall -c
CC=gcc

libmain.so: main.o
	$(CC) -shared -o libmain.so $^ -lraylib -lm
	make clean_obj

main.o: main.c
	$(CC) $(CARGS) $^ -lraylib -lm

clean_obj:
	rm -f *.o
