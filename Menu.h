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
    NOT_HANDLED
};

class Menu{
    SDL_Renderer* renderer;
    Button play, help, exit;
    Game &game;
    Scoreboard &scoreboard;
public:
    Menu(SDL_Renderer* renderer);
    void show();
    EventStatus handleEvent(SDL_Event *e);
};
#endif