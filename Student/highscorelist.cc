#include "highscorelist.hh"
#include "formatexception.hh"
#include "ioexception.hh"
#include <ios>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>

Student::HighScoreList::HighScoreList(const std::string &scoreFileName, int numHighScores)
    : scoreFileName_(scoreFileName)
    , numHighScores_(numHighScores)
{
    std::fstream f(scoreFileName_, std::ios_base::in);
    if (f.fail())
        return;

    std::string line;
    while (std::getline(f, line)) {
        std::istringstream iss(line);
        int score;
        std::string name;
        if (!(iss >> score))
            throw Common::FormatException("Failed to parse line " + line);

        // Get a char (the delimiting space) from the stream, it does not belong to the player name
        iss.get();
        if (!(std::getline(iss, name)))
            throw Common::FormatException("Failed to parse line " + line);

        ScoreEntry e = {score, name};
        scoreList.push_back(e);
    }
    std::sort(scoreList.begin(), scoreList.end(), compareHighScores);
}

Student::HighScoreList::~HighScoreList()
{
    saveScore();
}

bool Student::HighScoreList::isHighScore(int score) const
{
    for (int i = 0; i < scoreList.size(); ++i) {
        auto e = scoreList.at(i);
        if (score > e.score)
            return true;
        if (i + 1 >= numHighScores_)
            return false;
    }
    return true;
}

void Student::HighScoreList::addScore(int score, std::string name)
{
    Student::HighScoreList::ScoreEntry e = {score, name};
    auto i = scoreList.begin();
    for (; i != scoreList.end(); ++i)
        if (score > i->score)
            break;

    scoreList.insert(i, e);
}

void Student::HighScoreList::saveScore() const
{
    int numScores = std::min(numHighScores_, (int)scoreList.size());
    std::fstream f(scoreFileName_, std::ios_base::out);
    if (f.fail())
        throw Common::IoException(std::string("Could not write to ") + scoreFileName_);

    for (int i = 0; i < numScores; ++i) {
        auto e = scoreList.at(i);
        f << e.score << " " << e.name << std::endl;
    }
}

std::vector<Student::HighScoreList::ScoreEntry> Student::HighScoreList::getScoreList() const
{
    int numScores = std::min(numHighScores_, (int)scoreList.size());
    std::vector<Student::HighScoreList::ScoreEntry> result(numScores);
    for (int i = 0; i < numScores; ++i)
        result[i] = scoreList[i];
    return result;
}

bool Student::HighScoreList::compareHighScores(Student::HighScoreList::ScoreEntry &lhs, Student::HighScoreList::ScoreEntry &rhs)
{
    return lhs.score > rhs.score;
}
