#ifndef WARPDRIVEPLUSPLUS_HH
#define WARPDRIVEPLUSPLUS_HH

#include "shipengine.hh"
#include "galaxy.hh"
#include <QStatusBar>

namespace Student {

/*!
 * \brief The WarpDrivePlusPlus engine is like the WarpDrive engine, but better! Implements Common::ShipEngine.
 *
 * WarpDrivePlusPlus is slightly faster and more durable than the normal WarpDrive and has a higher range. It also makes "Wroom!" noises.
 */
class WarpDrivePlusPlus : public Common::ShipEngine {


public:
    /*!
     * \brief RANGE Maximum distance from origin to target
     */
    static const int RANGE ;

    /*!
     * \brief DISTANCE_PER_MOVEMENT Maximum speed of engine.
     */
    static const int DISTANCE_PER_MOVEMENT;

    /*!
     * \brief MAX_HEALTH Maximum amount of damage the engine can take
     */
    static const Health MAX_HEALTH;

    /*!
     * \brief MAX_DAMAGE_PER_START Maximum damage done to engine at start.
     */
    static const Health MAX_DAMAGE_PER_START;

    /*!
     * \brief MIN_DAMAGE_PER_START Minimum damage done to engine at start.
     */
    static const Health MIN_DAMAGE_PER_START;

    /*!
     * \brief WarpDrivePlusPlus Recommended constructor
     * \param galaxy The galaxy in which the engine will be used.
     */
    WarpDrivePlusPlus(std::shared_ptr<Student::Galaxy> galaxy);

    /*!
     * \brief onStart Damages the engine each time it's started. Makes "Wroom!" noises.
     */
    virtual void onStart();

    /*!
     * \brief getValidDestinations Gets a vector of star systems accessible by this engine
     * \param source The origin of the trip.
     * \return Possible destinations of a trip, excluding the source.
     */
    virtual Common::StarSystem::StarSystemVector getValidDestinations(std::shared_ptr<Common::StarSystem> source) const;

    /*!
     * \brief isValidTrip Checks if a trip from source to destination is possible.
     * \param source Source star system.
     * \param destination Destination star system.
     * \return True if the trip is possible, false if not.
     */
    virtual bool isValidTrip(std::shared_ptr<Common::StarSystem> source,
                            std::shared_ptr<Common::StarSystem> destination) const;

    /*!
     * \brief requiredTurns Calculates how long a trip would take.
     * \param source Source star system.
     * \param destination Destination star system.
     * \return Number of turns the trip takes.
     * \pre Parameters source and destination must not be nullptr.
     * \post Exception guarantee: nothrow.
     */
    virtual int requiredTurns(std::shared_ptr<Common::StarSystem> source,
                             std::shared_ptr<Common::StarSystem> destination) const;

    /*!
     * \brief setStatusbar Sets the statusbar for pionter for making "Wroom!" noises.
     * \param statusbar Pointer to the statusbar.
     */
    void setStatusbar(QStatusBar* statusbar);

private:
    /*!
     * \brief galaxy_ Galaxy in which the engine is used.
     */
    std::shared_ptr<Student::Galaxy> galaxy_;

    /*!
     * \brief statusbar_ Pointer to the main window's status bar.
     */
    QStatusBar* statusbar_;
};


} // Student

#endif // WARPDRIVEPLUSPLUS_HH
