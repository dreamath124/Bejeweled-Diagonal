#include "Menu.h"
#include <SDL2/SDL_ttf.h>
#include "Utilities.h"
#include <iostream>
#include "Window.h"

const char* Times_New_Roman = getAbsPath("assets/fonts/Times_New_Roman.ttf");
const int Button_Font_Size = 128;

SDL_Texture* getTextBox(const char* srcFont, int ptSize, const char* str, SDL_Renderer* renderer)
{
    TTF_Init();
    TTF_Font *font = TTF_OpenFont(srcFont, ptSize);
    if (font == NULL)
        return NULL;
    SDL_Surface* textSurface = TTF_RenderText_Blended(font, str, BLUE);
    if (textSurface == NULL)
        return NULL;
    SDL_Texture* text = SDL_CreateTextureFromSurface(renderer, textSurface);
    SDL_FreeSurface(textSurface);
    return text;
}

Menu::Menu(SDL_Renderer* renderer, Game &game): 
    renderer(renderer), 
    play(150, 300, 100, 50, 
        getTextBox(Times_New_Roman, Button_Font_Size, "PLAY", renderer),
        GREEN),
    help(150, 375, 100, 50, 
        getTextBox(Times_New_Roman, Button_Font_Size, "HELP", renderer),
        RED),
    exit(150, 450, 100, 50,
        getTextBox(Times_New_Roman, Button_Font_Size, "EXIT", renderer),
        NEON_PINK),
    game(game)

{
    
}

void Menu::show()
{
    play.render(renderer);
    help.render(renderer);
    exit.render(renderer);
    SDL_RenderPresent(renderer);
}

bool Menu::handleEvent(SDL_Event *e)
{ 
    if(play.handleEvent(e))
    {
        game.render(renderer);
        return true;
    }
    if(help.handleEvent(e))
    {
        //helpText.render();
        return false;;
    }
    if(exit.handleEvent(e))
        //Quit();
        return false;
    return false;
}