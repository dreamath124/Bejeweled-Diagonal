#ifndef __SCOREBOARD_h
#define __SCOREBOARD_h

#include <string>
#include <fstream>
#include <vector>
#include "Score.h"

class Scoreboard
{
    std::vector<Score> listScore;
    std::string src;
    friend class ScoreWindow;
public:
    Scoreboard(const std::string& name): 
        src(name)
    {
        src = name;
        readHistoryScore();
    }
    void readHistoryScore();
    void updateHistoryScore(Score score);
    void writeHistoryScore();
    void emptyHistoryScore();
};

#endif


