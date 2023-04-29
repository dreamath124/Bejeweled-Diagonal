#ifndef __UTILITIES_H
#define __UTILITIES_H

#include <iostream>
#include <fstream>
#include <SDL2/SDL.h>

static const SDL_Color 
    GREEN = {32, 192, 32, 0},
    BLUE = {32, 32, 192, 0},
    RED = {192, 32, 32},
    GREY = {128, 128, 128, 0},
    PINK = {255, },
    NEON_PINK = {255, 16, 240};

// hex code color
static const SDL_Color
    PURE_GREEN = {0x00, 0xff, 0x00, 0x00};

static const SDL_Color PURE_BLACK = {0, 0, 0, 0};

char* getAbsPath(const char* path);


#endif