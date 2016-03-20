all: main

main: main.cpp object.o
	g++ main.cpp -o main

object.o: object.h
	g++ -c object.h -o object.o

clean:
	rm -f object.o main
