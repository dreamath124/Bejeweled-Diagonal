#include "Menu.h"
#include <SDL2/SDL_ttf.h>
#include "Utilities.h"
#include <iostream>
#include "Window.h"

const char* Times_New_Roman = "assets/fonts/Digital7-rg1mL.ttf";
const int Button_Font_Size = 128;

Menu::Menu(SDL_Renderer* renderer, TextEngine& engine): 
    play(SDL_Rect{150, 300, 100, 50}, engine, "PLAY", PURE_BLACK),
    help(SDL_Rect{150, 375, 100, 50}, engine, "HELP", PURE_BLACK),
    exit(SDL_Rect{150, 450, 100, 50}, engine, "EXIT", PURE_BLACK),
    scoreboard(SDL_Rect{150, 500, 100, 50}, engine, "Exit", PURE_BLACK)
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