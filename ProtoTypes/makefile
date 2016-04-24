FLAGS=-lSDL -lSDL_image -std=c++11 -Wall -static-libstdc++ -lSDL_mixer

all: tanktest

tanktest: tanktest.cpp tank.h object.h sprite.o oursdllib.o bullet.h boom.h block.h scene.h gamescene.h menuscene.h
	g++ tanktest.cpp oursdllib.o sprite.o -o tanktest $(FLAGS)
	cp ./pics/* .

%.o: %.cpp %.h
	g++ -c $< $(FLAGS) -o $@

clean:
	rm -f *.o tanktest
	rm -f *.png *.bmp
