#include "Button.h"

bool Button::isInsideRect(SDL_Point point)
{
    return (
        point.x >= rect.x &&
        point.y >= rect.y &&
        point.x <= rect.x + rect.w &&
        point.y <= rect.y + rect.h
    );
}

Button::Button(int centerX, int centerY, int w, int h, SDL_Texture *texture, SDL_Color color) : 
    rect{centerX - w / 2, centerY - h / 2, w, h}, texture(texture), color(color)
{
}

bool Button::handleEvent(SDL_Event *e)
{
    if (e->type == SDL_MOUSEBUTTONUP)
    {
        SDL_Point mousePoint;
        SDL_GetMouseState(&mousePoint.x, &mousePoint.y);
        if (isInsideRect(mousePoint))
            return true;
    }
    return false;
}

void Button::render(SDL_Renderer* renderer)
{
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_RenderFillRect(renderer, &rect);
    SDL_RenderCopy(renderer, texture, NULL, &rect);
}
