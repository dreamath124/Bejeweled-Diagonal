#ifndef __HELP_H
#define __HELP_H

#include <SDL2/SDL.h>
#include "Utilities.h"
#include <fstream>

const char* fontPath = "assets/fonts/Digital7-rg1mL.ttf";

class Help{
    std::string src;
    std::string text;
public:
    Help(std::string src): src(src)
    {
        std::ifstream file(getAbsPath(src.c_str()));
        std::string buff;
        while(getline(file, buff))
        {
            text += buff + '\n';
        }
        file.close();
    }
    void render(SDL_Renderer* renderer)
    {
        TTF_Font *font = TTF_OpenFont(getAbsPath(fontPath), 32);
        SDL_Surface* textSurface = TTF_RenderText_Blended_Wrapped(font, text.c_str(), BLUE, 0);
        SDL_Texture* helpTextbox = SDL_CreateTextureFromSurface(renderer, textSurface);
        SDL_FreeSurface(textSurface);
        TTF_CloseFont(font);

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
        SDL_RenderClear(renderer);
        SDL_Rect helpRect;
        SDL_QueryTexture(helpTextbox, NULL, NULL, &helpRect.w, &helpRect.h);
        helpRect.x = helpRect.y = 0;
        SDL_RenderCopy(renderer, helpTextbox, NULL, &helpRect);
        SDL_RenderPresent(renderer);
        SDL_DestroyTexture(helpTextbox);
    }
};

#endif