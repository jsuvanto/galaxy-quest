#ifndef HIGHSCORE_HH
#define HIGHSCORE_HH

#include <string>
#include <vector>

namespace Student {

class HighScoreList
{
public:
    /*!
     * \brief The ScoreEntry struct A struct to contain a score entry (used instead of std::pair to be able to name atoms)
     */
    struct ScoreEntry
    {
        int score;
        std::string name;
    };

    /*!
     * \brief HighScoreList Construct a high score list
     * \param scoreFileName Name for a file containing the scores
     * \param numHighScores How many highest scores will be shown
     * \post Throws FormatException if score file is badly formatted
     */
    HighScoreList(const std::string &scoreFileName, int numHighScores);

    /*!
     * \brief ~HighScoreList Save the list to file
     * \post Throws IoException if file can't be written
     */
    ~HighScoreList();

    /*!
     * \brief isHighScore Check if a score ranks as high score
     * \param score Score to be checked
     * \return True if yes, False if not
     * \post nothrow
     */
    bool isHighScore(int score) const;

    /*!
     * \brief addScore Add a score to high score list (not checking if it ranks or not)
     * \param score Score to be added
     * \param name Name of the player
     * \post nothrow
     */
    void addScore(int score, std::string name);

    /*!
     * \brief saveScore Save scores to the file
     * \post Throws IoException if file can't be written
     */
    void saveScore() const;

    /*!
     * \brief getScoreList Get list of numHighScores highest scores
     * \return list of the highest listed scores
     * \post nothrow
     */
    std::vector<ScoreEntry> getScoreList() const;

private:
    /*!
     * \brief compareHighScores Comparer function for two high scores
     * \param lhs Operand 1
     * \param rhs Operand 2
     * \return True if lhs' score is larger than rhs'
     * \post nothrow
     */
    static bool compareHighScores(ScoreEntry &lhs, ScoreEntry &rhs);

    std::string scoreFileName_;
    int numHighScores_;

    std::vector<ScoreEntry> scoreList;
};

}

#endif // HIGHSCORE_HH
