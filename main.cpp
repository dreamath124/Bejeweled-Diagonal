#include <iostream>
#include <SDL2/SDL.h>
#include "Window.h"
#include "Menu.h"
#include "Utilities.h"
#include "Help.h"
#include "ScoreWindow.h"
#include "Scoreboard.h"
#include "TextEngine.h"

int main(int argc, char* argv[])
{
    Window window;
    TextEngine engine(window.renderer);
    Game game;
    Help help("helpText.txt");
    game.loadImageGallery(window.renderer);
    Scoreboard scoreboard("scores.txt");
    Menu menu(window.renderer, engine);
    ScoreWindow scoreWindow(scoreboard, engine);

    bool isRunning = true;
    EventStatus status = NOT_HANDLED;
    menu.show(window.renderer, engine);
    bool gameRunning = true;
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
        if (status == HELP) continue;
        if (status == NOT_HANDLED)
        {
            status = menu.handleEvent(&e);
            if (status == NOT_HANDLED) continue;
        }
        if (status == GAME)
        {
            if (!gameRunning) {
                SDL_RenderClear(window.renderer);
                game.renderGameOver(window.renderer, engine);
            }
            else 
            {
                gameRunning = game.handleEvent(&e, window.renderer, engine);
                game.render(window.renderer);
            }
        }
        if (status == HELP)
            help.render(window.renderer);
        if (status == SCOREBOARD)
        {
            SDL_RenderClear(window.renderer);
            scoreWindow.handleEvent(e);
            scoreWindow.renderUpdate();
        }
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