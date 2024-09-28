CC=gcc
OBJECT=omok

$(OBJECT): main.o util.o board.o
	$(CC) -o omok main.o util.o board.o

main.o: main.c board.h util.h
	$(CC) -c main.c

board.o: board.c board.h
	$(CC) -c board.c

util.o: util.c board.h
	$(CC) -c util.c

clean:
	rm -rf *.o $(OBJECT)
