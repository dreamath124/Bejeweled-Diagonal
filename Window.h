#ifndef __WINDOW_H
#define __WINDOW_H
#include <SDL2/SDL.h>
#include <cstdlib>
#include <ctime>
#include <string>
#include "Utilities.h"
class Window{
    const char* appIconLocation;
    const int INIT_WINDOW_WIDTH = 800;
    const int INIT_WINDOW_HEIGHT = 600;
public:
    SDL_Window* const window;
    SDL_Renderer* const renderer;
    SDL_Surface* const surface;
    Window(): 
        window(
            SDL_CreateWindow(
                "Bejeweled Diagonal", 
                SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 
                INIT_WINDOW_WIDTH, INIT_WINDOW_HEIGHT, 
                0
            )
        ),
        renderer(SDL_CreateRenderer(window, -1, 0)),
        surface(SDL_GetWindowSurface(window)),
        appIconLocation(getAbsPath("assets/images/appIcon.bmp"))
    {
        SDL_Surface* appIcon = SDL_LoadBMP(appIconLocation);
        SDL_SetWindowIcon(window, appIcon);
        SDL_SetHint(SDL_HINT_RENDER_DRIVER, "opengl");
        SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");
        std::srand(std::time(NULL));
    }
    ~Window()
    {
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
    }
};

#endif