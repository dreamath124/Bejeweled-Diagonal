#include "Menu.h"
#include <SDL2/SDL_ttf.h>
#include "Utilities.h"
#include <iostream>
#include "Window.h"

const char* Times_New_Roman = "assets/fonts/Digital7-rg1mL.ttf";
const int Button_Font_Size = 128;

Menu::Menu(SDL_Renderer* renderer): 
    play(150, 300, 100, 50, 
        getTextBox(Times_New_Roman, Button_Font_Size, "PLAY", renderer),
        GREEN),
    help(150, 375, 100, 50, 
        getTextBox(Times_New_Roman, Button_Font_Size, "HELP", renderer),
        RED),
    exit(150, 450, 100, 50,
        getTextBox(Times_New_Roman, Button_Font_Size, "EXIT", renderer),
        NEON_PINK),
    scoreboard(
        150, 500, 100, 50,
        getTextBox(Times_New_Roman, Button_Font_Size, "SCORE", renderer),
        PURE_BLACK
    )
{
    
}

void Menu::show(SDL_Renderer* renderer)
{
    play.render(renderer);
    help.render(renderer);
    exit.render(renderer);
    scoreboard.render(renderer);
    SDL_RenderPresent(renderer);
}

EventStatus Menu::handleEvent(SDL_Event *e)
{
    if (play.handleEvent(e))
        return GAME;
    if (help.handleEvent(e))
        return HELP;
    if (exit.handleEvent(e))
        return EXIT;
    if (scoreboard.handleEvent(e))
        return SCOREBOARD;
    return NOT_HANDLED;
}