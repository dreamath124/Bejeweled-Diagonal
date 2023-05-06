#ifndef __MENU_H
#define __MENU_H
#include <SDL2/SDL.h>
#include <iostream>
#include "Button.h"
#include "Game.h"
#include "Scoreboard.h"

enum EventStatus{
    GAME,
    HELP,
    EXIT,
    SCOREBOARD,
    NOT_HANDLED
};

class Menu{
    Button play, help, exit, scoreboard;
public:
    Menu(SDL_Renderer* renderer);
    void show(SDL_Renderer* renderer);
    EventStatus handleEvent(SDL_Event *e);
};
#endif