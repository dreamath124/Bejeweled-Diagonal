LDFLAGS := -lmingw32 -lSDL2main -lSDL2 -lSDL2_ttf -lSDL2_image

all: build/Bejeweled-Diagonal

build/Bejeweled-Diagonal: main.o Game.o Button.o Menu.o Utilities.o
	g++ $^ -o $@ $(LDFLAGS)

main.o: main.cpp Window.h Help.h
	g++ -c $< -o $@

Game.o: Game.cpp Game.h
	g++ -c $< -o $@

Button.o: Button.cpp Button.h
	g++ -c $< -o $@

Menu.o: Menu.cpp Menu.h Button.h Game.h
	g++ -c $< -o $@

Utilities.o: Utilities.cpp Utilities.h
	g++ -c $< -o $@

run:
	./build/Bejeweled-Diagonal

Debug:
	g++ -g main.cpp Game.cpp Menu.cpp Button.cpp -o debug/main $(LDFLAGS)

