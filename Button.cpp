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

Button::Button(SDL_Rect rect, TextEngine &engine, std::string label, SDL_Color color) : 
    rect(rect), engine(engine), label(label), bgColor(color)
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
    SDL_SetRenderDrawColor(renderer, bgColor.r, bgColor.g, bgColor.b, bgColor.a);
    SDL_RenderFillRect(renderer, &rect);
    engine.displayTextbox(label, rect.x + rect.w/2, rect.y + rect.h/2);
}
