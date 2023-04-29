#ifndef __MENU_H
#define __MENU_H
#include <SDL2/SDL.h>
#include <iostream>
#include "Button.h"
#include "Game.h"

enum ButtonList
{
    menu, 
    play,
    scores,
    help
};

class Menu{
    SDL_Renderer* renderer;
    Button play, help, exit;
    Game& game;
public:
    Menu(SDL_Renderer* renderer, Game &game);
    void show();
    bool handleEvent(SDL_Event *e);
};
#endif