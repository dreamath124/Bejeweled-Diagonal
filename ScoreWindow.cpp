#include "ScoreWindow.h"
#include "Utilities.h"

ScoreWindow::ScoreWindow(Scoreboard &listScore, TextEngine &engine) : 
                         page(0), alpha(listScore.listScore),
                         engine(engine)
{

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
    engine.displayTextbox(WINDOW_TITLE, 400, 30);
    for (int i = begin; i < end; ++i)
    {
        int y = 100 + (i - begin) * 50;
        engine.displayNumber(i, 50, y);
        engine.displayTextbox(alpha[i].name, 200, y);
        engine.displayNumber(alpha[i].duration, 400, y);
        engine.displayNumber(alpha[i].score, 600, y);
    }
}