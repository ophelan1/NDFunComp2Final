FLAGS=-lSDL -lSDL_image -std=c++11

all: tanktest

tanktest: tanktest.cpp tank.h object.h sprite.o oursdllib.o bullet.h boom.h
	g++ $^ -o tanktest $(FLAGS)

%.o: %.cpp %.h
	g++ -c $< $(FLAGS) -o $@

clean:
	rm -f *.o tanktest
