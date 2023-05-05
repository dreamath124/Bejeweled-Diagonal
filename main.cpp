#include <iostream>
#include <SDL2/SDL.h>
#include "Window.h"
#include "Menu.h"
#include "Utilities.h"
#include "Help.h"

int main(int argc, char* argv[])
{
    Window window;
    Game game;
    Help help("helpText.txt");
    game.loadImageGallery(window.renderer);
    //Scoreboard scoreboard("scores.txt", window);
    Menu menu(window.renderer);
    bool isRunning = true;
    EventStatus status = NOT_HANDLED;
    while(isRunning)
    {
        SDL_Event e;
        if (SDL_WaitEvent(&e))
        {
            if (e.type == SDL_QUIT)
            {
                isRunning = false;
                break;
            }
        }
        if (status == NOT_HANDLED)
        {
            menu.show();
            status = menu.handleEvent(&e);
        }
        if (status == GAME)
        {
            game.handleEvent(&e, window.renderer);
            game.render(window.renderer);
        }
        if (status == HELP)
            help.render(window.renderer);
        if (status == EXIT)
        {
            isRunning = false;
            continue;
        }
        SDL_RenderPresent(window.renderer);
        SDL_Delay(10);
    }
    return 0;
}