#include <iostream>
#include <SDL2/SDL.h>

int main(int argc, char* argv[])
{
    std::string appIconLocation = "appIcon.bmp";
    SDL_Window* window = SDL_CreateWindow("Bejeweled Diagonal", 
        SDL_WINDOWPOS_CENTERED, 
        SDL_WINDOWPOS_CENTERED, 800, 600, 0);
    SDL_Surface* appIcon = SDL_LoadBMP(appIconLocation.c_str());
    SDL_SetWindowIcon(window, appIcon);
    SDL_Delay(1000);
    return 0;
}