#include "TextEngine.h"
#include "Utilities.h"
TextEngine::TextEngine(SDL_Renderer* renderer):
    renderer(renderer)
{
    font = TTF_OpenFont(getAbsPath("assets/fonts/Digital7-rg1mL.ttf"), 48);
}

TextEngine::~TextEngine()
{
    TTF_CloseFont(font);
}

void TextEngine::displayTextbox(std::string displayText, int x, int y)
{
    SDL_Surface* textSurface = TTF_RenderText_Blended(font, displayText.c_str(), BLUE);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, textSurface);
    SDL_FreeSurface(textSurface);
    SDL_Rect rect;
    SDL_QueryTexture(texture, NULL, NULL, &rect.w, &rect.h);
    rect.x = x - rect.w / 2, rect.y = y - rect.h / 2;
    SDL_RenderCopy(renderer, texture, NULL, &rect);
    SDL_DestroyTexture(texture);
    SDL_RenderPresent(renderer);
}

void TextEngine::displayNumber(int number, int x, int y)
{
    displayTextbox(std::to_string(number), x, y);
}