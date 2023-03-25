SRC := *.cpp
FLAGS := $(shell sdl2-config --libs)

all:
	g++ $(SRC) -o Bejeweled-Diagonal $(FLAGS)
run:
	./Bejeweled-Diagonal