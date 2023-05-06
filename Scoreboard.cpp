#include "Scoreboard.h"
#include <algorithm>
void Scoreboard::readHistoryScore()
{
    std::ifstream reader(this->src);
    int size;
    reader >> size;
    for (int i = 0; i < size; ++i)
    {
        Score score;
        reader >> score;
        listScore.push_back(score);
    }
    reader.close();
}

void Scoreboard::updateHistoryScore(Score score)
{
    auto k = listScore.end();
    for (auto it = listScore.begin(); it != listScore.end(); ++it)
    {
        if (score > (*it))
        {
            k = it;
            break;
        }
    }
    listScore.insert(k, score);
}

void Scoreboard::writeHistoryScore()
{
    std::ofstream writer(src);
    writer << listScore.size() << '\n';
    for (Score score: listScore)
        writer << score;
}

void Scoreboard::emptyHistoryScore()
{
    std::ofstream writer(src);
    writer << 0;
    writer.close();
}