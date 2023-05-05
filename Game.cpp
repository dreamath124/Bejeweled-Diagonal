#include "Game.h"
#include <cmath>
#include "Utilities.h"
#include <bitset>
void Game::increaseScore(int length)
{
    score += 100;
}

const int baseX = 200;
const int baseY = 20;
const int cellEdge = 55;
const int textureGemEdge = 45;
const int gapGem = 5;

SDL_Color lightGrey{0xD3, 0xD3, 0xD3, 0},
    darkGray{0x69, 0x69, 0x69, 0};

Game::Game() : 
    boardGem(boardSize, std::vector<Gem>(boardSize)), 
    score(0), 
    focusCell({-1, -1}), 
    remove(boardSize),
    prevRow(boardSize, std::vector<int>(boardSize))
{
    for (int i = 0; i < boardSize; ++i)
        for (int j = 0; j < boardSize; ++j)
            boardGem[i][j] = getRandom();
    while (updateMatch())
        refill();
    score = 0;
}

bool Game::updateMatch()
{
    bool update = false;
    for (int i = -boardSize + 1; i < boardSize; ++i)
    {
        int begin = (i > 0 ? i : 0);
        Gem previous = UNDEFINED;
        for (int x = begin; x < boardSize && x - i < boardSize; ++x)
        {
            if (boardGem[x][x - i] == previous)
            {
                if (x - begin == 2)
                {
                    remove[x - 1][x - i - 1] = remove[x - 2][x - i - 2] = 1;
                    update = true;
                }
                if (x - begin >= 2)
                {
                    remove[x][x - i] = 1;
                    increaseScore(1);
                }
            }
            else
                begin = x;
            previous = boardGem[x][x - i];
        }
    }

    for (int i = 0; i < 2 * boardSize - 1; ++i)
    {
        int begin = (i >= boardSize ? boardSize - 1 : i);
        Gem previous = UNDEFINED;
        for (int x = begin; x >= 0 && i - x < boardSize; --x)
        {
            if (boardGem[x][i - x] == previous)
            {
                if (begin - x == 2)
                {
                    remove[x + 1][i - x - 1] = remove[x + 2][i - x - 2] = 1;
                    update = true;
                }
                if (begin - x >= 2)
                {
                    remove[x][i - x] = 1;
                    increaseScore(1);
                }
            }
            else
                begin = x;
            previous = boardGem[x][i - x];
        }
    }
    return update;
}

void Game::refill()
{
    for (int col = 0; col < boardSize; ++col)
    {
        int tmpRow = boardSize;
        for (int row = boardSize - 1; row >= 0; --row)
            if (!remove[col][row])
            {
                boardGem[col][--tmpRow] = boardGem[col][row];
                prevRow[col][tmpRow] = row;
            }
        for (int row = 0; row < tmpRow; ++row)
        {
            boardGem[col][row] = getRandom();
            prevRow[col][row] = row - tmpRow;
        }
        remove[col].reset();
    }
}

void Game::render(SDL_Renderer *renderer)
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_RenderClear(renderer);
    renderScore(renderer);
    for (int i = 0; i < boardSize; ++i)
        for (int j = 0; j < boardSize; ++j)
        {
            renderCellBackground(renderer, i, j);
            SDL_Rect gemRect{
                baseX + i * cellEdge + gapGem,
                baseY + j * cellEdge + gapGem,
                textureGemEdge,
                textureGemEdge};
            SDL_RenderCopy(renderer, gemTexture[boardGem[i][j]], NULL, &gemRect);
        }
    if (focusCell.first == -1)
        return;
    SDL_Rect cellRect{
        baseX + focusCell.first * cellEdge,
        baseY + focusCell.second * cellEdge,
        cellEdge,
        cellEdge};
    SDL_RenderCopy(renderer, focus, NULL, &cellRect);
    renderScore(renderer);
}

void Game::loadImageGallery(SDL_Renderer *renderer)
{
    std::string str[GEM_ITEMS] = {
        "red", "orange", "yellow", "green",
        "blue", "purple", "white"},
                dir = "assets/webp/Bejeweled_";
    for (int i = 0; i < GEM_ITEMS; ++i)
    {
        std::string address = dir + str[i] +
                              "_gem_promotional.webp";
        gemTexture[i] = IMG_LoadTexture(renderer, getAbsPath(address.c_str()));
    }
    focus = IMG_LoadTexture(renderer, getAbsPath("assets/images/selector.png"));
}

bool Game::handleEvent(SDL_Event *e, SDL_Renderer *renderer)
{
    if (e->type == SDL_MOUSEBUTTONDOWN)
    {
        int x, y;
        SDL_GetMouseState(&x, &y);
        if (x < baseX || y < baseY)
            return false;
        int row = (y - baseY) / cellEdge,
            col = (x - baseX) / cellEdge;
        if (row >= boardSize || col >= boardSize)
            return false;
        if (focusCell.first < 0)
        {
            focusCell = std::make_pair(col, row);
            SDL_Rect highlightRect{
                baseX + col * cellEdge,
                baseY + row * cellEdge,
                52,
                52,
            };
            return true;
        }
        if (abs(focusCell.first - col) + abs(focusCell.second - row) == 1)
        {
            std::swap(
                boardGem[focusCell.first][focusCell.second],
                boardGem[col][row]);
            renderSwap(renderer, col, row, focusCell.first, focusCell.second);
            bool loopUpdate = false;
            while (updateMatch())
            {
                loopUpdate = true;
                renderDisappear(renderer);
                refill();
                renderReset(renderer);
                render(renderer);
            }
            if (!loopUpdate)
            {
                std::swap(
                    boardGem[focusCell.first][focusCell.second],
                    boardGem[col][row]);
                renderSwap(renderer, col, row, focusCell.first, focusCell.second);
            }
            focusCell.first = -1;
            return true;
        }
        else if (focusCell.first > -1)
        {
            focusCell = std::make_pair(col, row);
            return true;
        }
    }
    return false;
}

void Game::renderScore(SDL_Renderer *renderer)
{
    std::string scoreString(9, ' ');
    std::string tmp = std::to_string(score);
    scoreString.replace(9 - tmp.size(), tmp.size(), tmp);
    SDL_Texture *scoreTexture = getTextBox("assets/fonts/Digital7-rg1mL.ttf",
                                           64, scoreString.c_str(), renderer);
    SDL_Texture *titleTexture = getTextBox("assets/fonts/Digital7-rg1mL.ttf",
                                           64, "Score", renderer);
    SDL_Rect scoreRect{10, 100, 100, 50}, headerRect{10, 150, 100, 50};
    SDL_RenderCopy(renderer, titleTexture, NULL, &scoreRect);
    SDL_RenderCopy(renderer, scoreTexture, NULL, &headerRect);
    SDL_DestroyTexture(scoreTexture);
    SDL_DestroyTexture(titleTexture);
}

/// @brief
///     Swap gem in pos(x, y) and pos(u, v)
/// @param x
/// @param y
/// @param u
/// @param v
void Game::renderSwap(SDL_Renderer *renderer, int x, int y, int u, int v)
{
    uint32_t tick = SDL_GetTicks(), prevTick;
    bool moving = true;
    int velocity = 200;
    double ds = 0;
    int activeX = sgn(u - x);
    int activeY = sgn(v - y);
    SDL_Delay(16);
    while (ds <= cellEdge)
    {
        prevTick = tick;
        tick = SDL_GetTicks();
        ds += velocity * (tick - prevTick) * 0.001;
        SDL_FRect rXY = {
                      baseX + cellEdge * x + gapGem + activeX * ds,
                      baseY + cellEdge * y + gapGem + activeY * ds,
                      textureGemEdge,
                      textureGemEdge},
                  rUV = {
                    baseX + cellEdge * u + gapGem - activeX * ds, 
                    baseY + cellEdge * v + gapGem - activeY * ds, 
                    textureGemEdge, 
                    textureGemEdge};
        renderCellBackground(renderer, x, y);
        renderCellBackground(renderer, u, v);
        SDL_RenderCopyF(renderer, gemTexture[boardGem[x][y]],
                        NULL, &rXY);
        SDL_RenderCopyF(renderer, gemTexture[boardGem[u][v]],
                        NULL, &rUV);
        SDL_RenderPresent(renderer);
        SDL_Delay(16);
    }
}

void Game::renderCellBackground(SDL_Renderer *renderer, int x, int y)
{
    SDL_Color color = ((x + y) % 2 ? lightGrey : darkGray);
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_Rect cellRect{
        baseX + x * cellEdge,
        baseY + y * cellEdge,
        cellEdge,
        cellEdge};
    SDL_RenderFillRect(renderer, &cellRect);
}

void Game::renderDisappear(SDL_Renderer *renderer)
{
    for (int scene = 0; scene < 5; ++scene)
    {
        SDL_Delay(32);
        for (int i = 0; i < boardSize; ++i)
            for (int j = 0; j < boardSize; ++j)
                if (remove[i][j])
                {
                    renderCellBackground(renderer, i, j);
                    SDL_Rect zoomGem{
                        baseX + i * cellEdge + scene * 5 + 5,
                        baseY + j * cellEdge + scene * 5 + 5,
                        textureGemEdge - scene * 10,
                        textureGemEdge - scene * 10};
                    SDL_RenderCopy(renderer, gemTexture[boardGem[i][j]], NULL, &zoomGem);
                }
        SDL_RenderPresent(renderer);
    }
}

void Game::renderReset(SDL_Renderer* renderer)    
{
    int longestMove = 0;
    for (int i = 0; i < boardSize; ++i)
        if (prevRow[i][0] < -longestMove)
            longestMove = -prevRow[i][0];
    longestMove *= cellEdge;
    float ds = 0;
    SDL_Rect clearRect = {baseX, 0, boardSize * cellEdge, boardSize * cellEdge};
    while(ds <= longestMove)
    {
        SDL_Delay(16);
        ds += 3.2;
        for (int i = 0; i < boardSize; ++i)
            for (int j = 0; j < boardSize; ++j)
                renderCellBackground(renderer, i, j);
        for (int i = 0; i < boardSize; ++i) 
            for (int j = 0; j < boardSize; ++j)
            {
                float diff = (prevRow[i][j] - j) * cellEdge + ds;
                if (diff > 0) diff = 0;
                SDL_FRect gemRect={
                    baseX + i * cellEdge + gapGem,
                    diff + baseY + j * cellEdge + gapGem , 
                    textureGemEdge,
                    textureGemEdge
                };
                if (gemRect.x > 0)
                    SDL_RenderCopyF(
                        renderer,
                        gemTexture[boardGem[i][j]],
                        NULL,
                        &gemRect
                    );
            }
        SDL_RenderPresent(renderer);
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
        SDL_RenderFillRect(renderer, &clearRect);
    }
}