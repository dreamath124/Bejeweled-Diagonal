#ifndef BUTTON_H
#define BUTTON_H
#include <SDL2/SDL.h>
#include <iostream>
#include <functional>

const int BUTTON_HEIGHT = 50;
const int BUTTON_WIDTH = 100;


class Button{
private:
    SDL_Rect rect;
    SDL_Texture* texture;
    SDL_Color color;
public:
    ~Button()
    {
        SDL_DestroyTexture(texture);
    }
    void render(SDL_Renderer* renderer);
    Button(int centerX, int centerY, int w, int h, SDL_Texture *texture, SDL_Color color);
    bool handleEvent(SDL_Event *e);
    bool isInsideRect(SDL_Point point);
};
#endif