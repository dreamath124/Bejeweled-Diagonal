#ifndef __UTILITIES_H
#define __UTILITIES_H

#include <iostream>
#include <fstream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

static const SDL_Color 
    GREEN = {0, 0x80, 0, 0},
    BLUE = {0, 0, 0xFF, 0},
    RED = {0x8B, 0x0, 0x0, 0x0},
    GREY = {0x80, 0x80, 0x80, 0},
    PINK = {0xFF, 0x0F, 0x0F, 0},
    NEON_PINK = {255, 16, 240};

// hex code color
static const SDL_Color
    PURE_GREEN = {0x00, 0xff, 0x00, 0x00};

static const SDL_Color PURE_BLACK = {0, 0, 0, 0};

char* getAbsPath(const char* path);

SDL_Texture* getTextBox(const char* srcFont, int ptSize, const char* str, SDL_Renderer* renderer);

int sgn(int x);

#endif