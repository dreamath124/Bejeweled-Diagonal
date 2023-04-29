#include <iostream>
#include <SDL2/SDL.h>
#include "Window.h"
#include "Menu.h"
#include "Utilities.h"
enum Context{
    MENU,
    GAME
};

int main(int argc, char* argv[])
{
    Window window;
    Game game;
    game.loadImageGallery(window.renderer);
    Menu menu(window.renderer, game);
    bool isRunning = true;
    Context context = MENU;
    while(isRunning)
    {
        SDL_Event e;
        while(SDL_PollEvent(&e))
        {
            if (e.type == SDL_QUIT)
            {
                isRunning = false;
                break;
            }
            if (context == GAME)
                game.handleEvent(&e);
            else
                if (menu.handleEvent(&e))
                    context = GAME;
        }
        if (context == GAME) 
            game.render(window.renderer); 
        else {
            menu.show();
            SDL_SetRenderDrawColor(window.renderer, 0, 0, 0, 255);
        }
        SDL_RenderPresent(window.renderer);
        SDL_Delay(16);
    }
    SDL_Quit();
    return 0;
}