#include "Score.h"

std::ifstream& operator >> (std::ifstream &is, Score &score)
{
    is >> score.name 
    >> score.duration
    >> score.startTime
    >> score.score;
    return is;
}

std::ofstream& operator << (std::ofstream &os, Score &score)
{
    os << score.name << ' '
    << score.duration << ' '
    << score.startTime << ' '
    << score.score << '\n';
    return os;
}