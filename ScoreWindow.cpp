#include "ScoreWindow.h"
#include "Utilities.h"

ScoreWindow::ScoreWindow(Window &window,
                         Scoreboard &listScore) : 
                         page(0), renderer(window.renderer), alpha(listScore.listScore)
{
    TTF_Font *font = TTF_OpenFont(srcFont, 24);
    SDL_Surface *fontSurface = TTF_RenderText_Solid(font, WINDOW_TITLE, NEON_PINK);
    texture = SDL_CreateTextureFromSurface(renderer, fontSurface);
    SDL_FreeSurface(fontSurface);
    TTF_CloseFont(font);
}


bool ScoreWindow::handleEvent(SDL_Event &e)
{
    int prevPage = page;
    int maxPage = alpha.size() / PAGE_SIZE;
    if (e.key.keysym.sym == SDLK_RIGHT && page < maxPage - 1) ++page;
    if (e.key.keysym.sym == SDLK_LEFT && page > 0) --page;
    return page != prevPage;
}

void ScoreWindow::renderUpdate()
{
    int begin = page *PAGE_SIZE,
    end = std::min(begin + PAGE_SIZE, (int)alpha.size());
    SDL_Rect headerRect{350, 0, 100, 50};
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, texture, NULL, &headerRect);
    for (int i = begin; i < end; ++i)
    {
        SDL_Texture* texture = getTextBox(
            fontPath, 36, (std::to_string(i) + ". " + alpha[i].name).c_str(), renderer);
        SDL_Rect rect;
        SDL_QueryTexture(texture, NULL, NULL, &rect.w, &rect.h);
        rect.x = 100;
        rect.y = (i - begin + 1) * 50;
        SDL_RenderCopy(renderer, texture, NULL, &rect);
    }
    SDL_RenderPresent(renderer);
}