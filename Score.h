#ifndef SCORE_H
#define SCORE_H
#include <fstream>
#include <string>


class Score{
private:
    std::string name;
    int startTime;
    int duration;
    int score;
    friend class ScoreWindow;
public:
    bool operator >(const Score &other)
    {
        if (score == other.score)
            return duration < other.duration;
        return score < other.score;
    }
    friend std::ifstream& operator >> (std::ifstream &is, Score &score);
    friend std::ofstream& operator << (std::ofstream &os, Score &score);
};

#endif