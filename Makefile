SRC := *.cpp
FLAGS := $(shell sdl2-config --libs) -lSDL2_ttf -lSDL2_image

all:
	g++ $(SRC) -o Bejeweled-Diagonal $(FLAGS)
run:
	./Bejeweled-Diagonal