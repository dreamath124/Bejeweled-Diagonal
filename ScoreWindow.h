#ifndef __SCOREWINDOW_H
#define __SCOREWINDOW_H
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <cmath>
#include <vector>
#include "Window.h"
#include "Score.h"
#include "Scoreboard.h"

class ScoreWindow
{
    SDL_Texture* texture;
    SDL_Renderer* const renderer;
    int page;

    const char* WINDOW_TITLE = "Highest scores";
    const int PAGE_SIZE = 10;
    const char* srcFont = "assets/fonts/Times_New_Roman.ttf";
    const char* fontPath = "assets/fonts/Digital7-rg1mL.ttf";
    const std::vector<Score> &alpha;
public:
    ScoreWindow(
        Window &window,
        Scoreboard &listScore
    );
    bool handleEvent(SDL_Event &e);
    void renderUpdate();
};
#endif