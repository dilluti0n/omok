CC=gcc
OBJECT=omok

$(OBJECT): main.o util.o board.o game.o
	$(CC) -o omok main.o util.o board.o game.o

main.o: main.c board.h util.h
	$(CC) -c main.c

board.o: board.c board.h util.h
	$(CC) -c board.c

util.o: util.c board.h util.h
	$(CC) -c util.c

game.o: game.c board.h util.h game.h
	$(CC) -c game.c

clean:
	rm -rf *.o $(OBJECT)
