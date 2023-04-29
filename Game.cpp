#include "Game.h"
#include <cmath>
#include "Utilities.h"
void Game::increaseScore()
{
    score += 100 * rand() % 4;
}

const int baseX = 200;
const int baseY = 20;
const int cellEdge = 55;
const int textureGemEdge = 45;
const int gapGem = 5;

std::vector<int> Game::checkMatching(int x, int y)
{
    int leftUpMatch = 0, leftDownMatch = 9;
    int rightUpMatch = 0, rightDownMatch = 9;
    for (int i = 0; x >= i && y >= i; ++i)
        if (boardGem[x][y] != boardGem[x - i][y - i])
        {
            leftUpMatch = i - 1;
            break;
        }
    for (int i = 0; x + i < 10 && y >= i; ++i)
        if (boardGem[x][y] != boardGem[x + i][y - i])
        {
            leftDownMatch = i - 1;
            break;
        }
    for (int i = 0; x + i <= 10 && y + i <= 10; ++i)
        if (boardGem[x][y] != boardGem[x + i][y + 1])
        {
            rightDownMatch = i - 1;
            break;
        }
    for (int i = 0; x >= i && y + i < 10; ++i)
        if (boardGem[x][y] != boardGem[x - i][y + i])
        {
            rightUpMatch = i - 1;
            break;
        }
    return std::vector<int>({leftUpMatch, leftDownMatch, 
                rightUpMatch, rightDownMatch});
}

void Game::render(SDL_Renderer* renderer)
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_RenderClear(renderer);
    SDL_Color whiteSmoke{0xF5, 0xF5, 0xF5, 0},
        lightGrey{0xD3, 0xD3, 0xD3, 0};
    for (int i = 0; i < boardSize; ++i)
        for (int j = 0; j < boardSize; ++j)
        {
            if ((i + j) % 2 == 1)
                SDL_SetRenderDrawColor(renderer, lightGrey.r, lightGrey.g, lightGrey.b, lightGrey.a);
            else SDL_SetRenderDrawColor(renderer, whiteSmoke.r, whiteSmoke.g, whiteSmoke.b, whiteSmoke.a);
            SDL_Rect gemRect{
                baseX + i * cellEdge + gapGem,
                baseY + j * cellEdge + gapGem,
                textureGemEdge,
                textureGemEdge
            };
            SDL_Rect cellRect{
                baseX + i * cellEdge,
                baseY + j * cellEdge,
                cellEdge,
                cellEdge
            };
            SDL_RenderFillRect(renderer, &cellRect);
            SDL_RenderCopy(renderer, gemTexture[boardGem[i][j]], NULL, &gemRect);
        }
}

void Game::loadImageGallery(SDL_Renderer* renderer)
{
    std::string str[GEM_ITEMS] = {
        "red", "orange", "yellow", "green",
        "blue", "purple", "white"
    },
    dir = "assets/webp/Bejeweled_";
    for (int i = 0; i < GEM_ITEMS; ++i)
    {
        std::string address = dir + str[i] + 
            "_gem_promotional.webp";
        gemTexture[i] = IMG_LoadTexture(renderer, getAbsPath(address.c_str()));
        //SDL_SetTextureBlendMode(gemTexture[i], SDL_BLENDMODE_NONE);
    }
}

bool Game::handleEvent(SDL_Event *e)
{
    if (e->type == SDL_MOUSEBUTTONDOWN)
    {
        int x, y;
        SDL_GetMouseState(&x, &y);
        if (x < baseX || y < baseY) return false;
        int row = (y - baseY) / cellEdge, 
            col = (x - baseX) / cellEdge;
        if (row >= 10 || col >= 10) return false;
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
        else{
            if (abs(focusCell.first - col) + abs(focusCell.second - row) == 1)
            {
                std::swap(boardGem[focusCell.first][focusCell.second],
                        boardGem[col][row]);
                focusCell.first = -1;
            }
                
        }
    }
    return false;
}