#ifndef __ENGINE_H
#define __ENGINE_H
#include <map>
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <vector>

class TextEngine{
    SDL_Renderer* renderer;
    TTF_Font* font;
public:
    TextEngine(SDL_Renderer* renderer);
    ~TextEngine();
    void displayTextbox(std::string displayText, int x, int y);
    void displayNumber(int number, int x, int y);
    void showGlyph();
};

#endif