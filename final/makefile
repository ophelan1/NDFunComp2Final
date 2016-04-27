FLAGS=-lSDL -lSDL_image -std=c++11 -Wall -static-libstdc++ -lSDL_mixer
EXEC=tanktest
SOURCES=tanktest.cpp tank.h object.h sprite.o oursdllib.o bullet.h boom.h block.h scene.h gamescene.h menuscene.h bigboom.h
COMPILABLE=tanktest.cpp oursdllib.o sprite.o
CC=g++

all: $(EXEC)

$(EXEC): $(SOURCES)
	$(CC) $(COMPILABLE) -o $(EXEC) $(FLAGS)
	cp ./pics/* .

%.o: %.cpp %.h
	$(CC) -c $< $(FLAGS) -o $@

clean:
	rm -f *.o $(EXEC)
	rm -f *.png *.bmp
