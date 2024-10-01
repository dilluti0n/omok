CC=gcc
OBJECT=omok

$(OBJECT): main.o util.o board.o game.o cursor.o console.o io.o keymap.o
	$(CC) -o omok main.o util.o board.o game.o cursor.o io.o keymap.o console.o

main.o: main.c board.h util.h game.h
	$(CC) -c main.c

board.o: board.c board.h util.h game.h
	$(CC) -c board.c

game.o: game.c board.h util.h game.h
	$(CC) -c game.c

cursor.o: cursor.c cursor.h board.h game.h
	$(CC) -c cursor.c

console.o: console.c console.h keymap.h game.h
	$(CC) -c console.c

io.o: io.c util.h keymap.h board.h game.h
	$(CC) -c io.c

util.o: util.c board.h util.h game.h
	$(CC) -c util.c

keymap.o: keymap.c keymap.h game.h
	$(CC) -c keymap.c

clean:
	rm -rf *.o $(OBJECT)
