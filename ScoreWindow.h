#ifndef __SCOREWINDOW_H
#define __SCOREWINDOW_H
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <cmath>
#include <vector>
#include "Window.h"
#include "Score.h"
#include "Scoreboard.h"
#include "TextEngine.h"

class ScoreWindow
{
    int page;
    TextEngine &engine;
    std::string WINDOW_TITLE = "Highest scores";
    const int PAGE_SIZE = 10;
    const std::vector<Score> &alpha;
public:
    ScoreWindow(Scoreboard& scoreboard, TextEngine& enginPe);
    bool handleEvent(SDL_Event &e);
    void renderUpdate();
};
#endif