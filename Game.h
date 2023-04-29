#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <bits/stl_pair.h>
enum Gem{
    Red,
    Yellow,
    Orange,
    Green,
    Blue,
    Purple,
    White,
    GEM_ITEMS = 7
};

const int boardSize = 10;

class Game{
    std::vector<std::vector<Gem>> boardGem;
    int score;
    std::pair<int, int> focusCell;
    SDL_Texture* gemTexture[GEM_ITEMS];
public:
    Game(): boardGem(boardSize, std::vector<Gem>(boardSize)), score(0), focusCell({-1, -1})
    {
        for (int i = 0; i < boardSize; ++i)
            for (int j = 0; j < boardSize; ++j)
                boardGem[i][j] = getRandom();
    }
    void increaseScore();
    std::vector<int> checkMatching(int x, int y);
    void render(SDL_Renderer *renderer);
    void loadImageGallery(SDL_Renderer *renderer);
    bool handleEvent(SDL_Event *e);
    void changeFocusCell(int x, int y)
    {
        focusCell.first = x;
        focusCell.second = y;
    }
    Gem getRandom()
    {
        return static_cast<Gem>(std::rand() % GEM_ITEMS);
    }
};