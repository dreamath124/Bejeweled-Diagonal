#ifndef BUTTON_H
#define BUTTON_H
#include <SDL2/SDL.h>
#include <iostream>
#include <functional>
#include "TextEngine.h"
const int BUTTON_HEIGHT = 50;
const int BUTTON_WIDTH = 100;


class Button{
private:
    SDL_Rect rect;
    TextEngine &engine;
    std::string label;
    SDL_Color bgColor;
public:
    Button(SDL_Rect rect, TextEngine &engine, std::string label, SDL_Color color);
    void render(SDL_Renderer* renderer);
    bool handleEvent(SDL_Event *e);
    bool isInsideRect(SDL_Point point);
};
#endif