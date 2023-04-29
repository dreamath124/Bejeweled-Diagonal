#include "Utilities.h"
char* getAbsPath(const char* path)
{
    static const char* gameDirectory = SDL_GetBasePath();
    char* res = strcpy(new char[256], gameDirectory);
    strcat(res, path);
    return res;
}