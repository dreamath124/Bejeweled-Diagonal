#include "Utilities.h"
char* getAbsPath(const char* path)
{
    static const char* gameDirectory = SDL_GetBasePath();
    static char* res = new char[1024];
    strcpy(res, gameDirectory);
    strcat(res, path);
    return res;
}
SDL_Texture* getTextBox(const char* srcFont, int ptSize, const char* str, SDL_Renderer* renderer)
{
    TTF_Init();
    TTF_Font *font = TTF_OpenFont(getAbsPath(srcFont), ptSize);
    if (font == NULL)
        return NULL;
    SDL_Surface* textSurface = TTF_RenderText_Blended(font, str, BLUE);
    if (textSurface == NULL)
        return NULL;
    SDL_Texture* text = SDL_CreateTextureFromSurface(renderer, textSurface);
    SDL_FreeSurface(textSurface);
    TTF_CloseFont(font);
    return text;
}

int sgn(int x)
{
    if (x > 0) return 1;
    if (x < 0) return -1;
    return 0;
}
