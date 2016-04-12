all: tanktest

tanktest: tanktest.cpp tank.h object.h sprite.o oursdllib.o
	g++ $^ -o tanktest -lSDL -lSDL_image

%.o: %.cpp %.h
	g++ -c $< -lSDL -lSDL_image -o $@

main: main.cpp sprite.h
	g++ main.cpp -o main

clean:
	rm -f *.o main tanktest
