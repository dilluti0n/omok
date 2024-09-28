omok: main.o util.o board.o
	g++ -o omok main.o util.o board.o

main.o: main.cpp board.h util.h
	g++ -c main.cpp

board.o: board.cpp board.h
	g++ -c board.cpp

util.o: util.cpp board.h
	g++ -c util.cpp

clean:
	rm -rf *.o omok w4_lab2_problem2.zip

eval: clean
	zip w4_lab2_problem2.zip ./*
