#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <bits/stl_pair.h>
#include <bitset>
#include "TextEngine.h"
enum Gem{
    Red,
    Yellow,
    Orange,
    Green,
    Blue,
    Purple,
    White,
    GEM_ITEMS = 7,
    UNDEFINED
};

enum RenderState{
    notmove,
    swap,
    slide
};

const int boardSize = 8;
const int maxMove = 24;

class Game{
    std::vector<std::vector<Gem>> boardGem;
    std::vector<std::bitset<boardSize>> remove;
    std::vector<std::vector<int>> prevRow;
    int score, time;
    std::pair<int, int> focusCell;
    SDL_Texture* gemTexture[GEM_ITEMS];
    SDL_Texture* focus;
    SDL_Texture* background;
    int countMove;
public:
    Game();
    void increaseScore(int match);
    bool updateMatch();
    void refill();
    void render(SDL_Renderer *renderer);
    void loadImageGallery(SDL_Renderer *renderer);
    bool handleEvent(SDL_Event *e, SDL_Renderer *renderer, TextEngine &engine);
    void renderScore(SDL_Renderer *renderer);
    void renderSwap(SDL_Renderer* renderer, int x, int y, int u, int v);
    void renderCellBackground(SDL_Renderer *renderer, int x, int y);
    void renderDisappear(SDL_Renderer *renderer);
    void renderReset(SDL_Renderer* renderer);
    void renderGameOver(SDL_Renderer *renderer, TextEngine& engine);
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