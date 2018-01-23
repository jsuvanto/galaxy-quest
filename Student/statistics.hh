#ifndef STATISTICS_HH
#define STATISTICS_HH

#include "istatistics.hh"
namespace Student {

/*!
 * \brief Defines the interface for the concrete statistics
 * \author Juha Suvanto
 * \invariant getCreditBalance() >= MAX_LOAN_ALLOWANCE && getPoints() >= 0
 */
class Statistics : public Common::IStatistics
{
public:
    /*!
     * \brief Default constructor for the interface.
     * \post getCreditBalance() == 0 && getLostShips() == 0 && getSavedShips() == 0 && getPoints() == 0. Exception guarantee: nothrow
     */
    Statistics();


    /*!
     * \brief addSavedShip Increases the number of robbed ships by one.
     * \post Exception guarantee: nothrow
     */
    void addSavedShip();

    /*!
      * \brief getSavedShips Returns the number of robbed ships.
      * \post Exception guarantee: nothrow
      */
    unsigned int getSavedShips() const;

    /*!
     * \brief addLostShip Increases the number of lost ships by one.
     * \post Exception guarantee: nothrow
     */
    void addLostShip();

    /*!
     * \brief getLostShips Returns the number of lost ships.
     * \post Exception guarantee: nothrow
     */
    unsigned int getLostShips() const;

    /*!
     * \brief addPoints increses the points of the player by the given amount
     * \param amount Points to be added
     * \post Exception guarantee: nothrow
     */
    void addPoints(unsigned int amount);

    /*!
     * \brief reducePoints Reduces the points of the player by the given amount
     * \param amount Points to be reduced
     * \exception StateException, if the invariant gets broken
     * \post Exception guarantee: strong
     */
    void reducePoints(unsigned int amount);

    /*!
     * \brief getPoints Returns the total points of the players
     * \post Exception guarantee: nothrow
     */
    unsigned int getPoints() const;

    /*!
     * \brief addCredits adds credits to the player's account
     * \param amount Credits to be added
     * \post Exception guarantee: nothrow
     */
    void addCredits(unsigned int amount);

    /*!
     * \brief reduceCredits reduces credits from the player's account
     * \param amount Credits to be removed
     * \exception StateException, if the invariant gets broken.     
     * \post Exception guarantee: strong
     */
    void reduceCredits(unsigned int amount);

    /*!
     * \brief getCreditBalance returns the number of credits left
     * \post Exception guarantee: nothrow
     */
    int getCreditBalance() const;

private:
    /*!
    * \brief saved_ships_ stores the number of saved ships.
    */
    unsigned int saved_ships_;

    /*!
     * \brief lost_ships_ stores the number of ships removed from the galaxy.
     */
    unsigned int lost_ships_;

    /*!
     * \brief points_ stores the player's points.
     */
    unsigned int points_;

    /*!
     * \brief credits_ stores the player's credits.
     */
    unsigned int credits_;

    /*!
     * \brief invariant Tests the class invariant.
     */
    void invariant() const;

    /*!
     * \brief MAX_LOAN_ALLOWANCE How much debt the player can have.
     */
    unsigned int MAX_LOAN_ALLOWANCE = 0;

    friend class StatisticsTest;    // Allow the test class to access our private variables and functions.

};
}//Student

#endif // STATISTICS_HH
