#ifndef EVENTHANDLER_HH
#define EVENTHANDLER_HH

namespace Student {
    class EventHandler;
}

#include "galaxy.hh"
#include "ieventhandler.hh"
#include "point.hh"
#include "starsystem.hh"
#include "statistics.hh"
#include "galaxymap.hh"
#include "playership.hh"
#include "galaxy.hh"
#include "gamerunner.hh"
#include "mainwindow.hh"

#include <vector>
#include <QStatusBar>


namespace Student {
class EventHandler: public Common::IEventHandler
{
public:
    /*!
     * \brief EventHandler Creates an event handler.
     * \param galaxy Galaxy in which the events happen.
     */
    EventHandler(std::shared_ptr<Student::Galaxy> galaxy);
    ~EventHandler();

    /*!
     * \brief shipSpawned Tell galaxy map to register a new ship.
     * \param ship The ship.
     * \pre Galaxy map has been set.
     */
    virtual void shipSpawned(std::shared_ptr<Common::Ship> ship);

    /*!
     * \brief shipRemoved Tell galaxy map to remove a ship. Add more ships if none are left.
     * \param ship The ship.
     * \pre Galaxy map and game runner have been set.
     */
    virtual void shipRemoved(std::shared_ptr<Common::Ship> ship);

    /*!
     * \brief shipRelocated Check whether a ship should be robbed.
     * \param ship The relocated ship.
     * \param starSystem The system or interstellar space (nullptr) where the ship came from.
     * \pre Player ship has been set.
     */
    virtual void shipRelocated(std::shared_ptr<Common::Ship> ship,
                               std::shared_ptr<Common::StarSystem> starSystem);

    /*!
     * \brief shipMoved Tell galaxy map to move a ship on the map.
     * \param ship The ship.
     * \param origin Origin point, not used.
     * \param target Target point.
     * \pre Galaxy map has been set.
     */
    virtual void shipMoved(std::shared_ptr<Common::Ship> ship,
                           Common::Point origin,
                           Common::Point target);

    /*!
     * \brief exceptionInExecution Displays a message box about the exception.
     * \param ship Ship that caused the exception.
     * \param msg Error message of the exception.
     */
    virtual void exceptionInExecution(std::shared_ptr<Common::Ship> ship, std::string const& msg);

    /*!
     * \brief distressOn Tell galaxy map to draw a distress icon.
     * \param ship The ship in distress.
     * \pre Galaxy map has been set.
     */
    virtual void distressOn(std::shared_ptr<Common::Ship> ship);

    /*!
     * \brief distressOff Tell galaxy map to remove a distress icon.
     * \param ship The ship no longer in distress.
     * \pre Galaxy map has been set.
     */
    virtual void distressOff(std::shared_ptr<Common::Ship> ship);

    /*!
     * \brief shipAbandoned Tell galaxy to remove a ship, and increment the lost ship counter.
     * \param ship The abandoned ship.
     * \pre Statistics object has been set.
     */
    virtual void shipAbandoned(std::shared_ptr<Common::Ship> ship);

    /*!
     * \brief setStatsPointer Set internal pointer to statistics handler.
     * \param statistics Pointer to stats.
     */
    void setStatsPointer(std::shared_ptr<Student::Statistics> statistics);

    /*!
     * \brief setGalaxyMap Set pointer to galaxy map.
     * \param galaxymap Pointer to galaxy map.
     */
    void setGalaxyMap(std::shared_ptr<Student::GalaxyMap> galaxymap);

    /*!
     * \brief setPlayerShip Set pointer to player ship.
     * \param playership Pointer to player ship.
     */
    void setPlayerShip(std::shared_ptr<Student::PlayerShip> playership);

    /*!
     * \brief starSystemClicked Handler for star system click event.
     * \param system The system that was clicked.
     * \pre Statusbar and player ship have been set.
     */
    void starSystemClicked(std::shared_ptr<Common::StarSystem> system);    

    /*!
     * \brief setGameRunner Sets the game runner so eventhandler can spawn more ships.
     * \param gamerunner Pointer to the game runner.
     */
    void setGameRunner(std::shared_ptr<Common::IGameRunner> gamerunner);

    /*!
     * \brief showStarSystemInfo Shows star system info in the statusbar.
     * \param system The star system
     * \pre Statusbar has been set.
     */
    void showStarSystemInfo(std::shared_ptr<Common::StarSystem> system);

    /*!
     * \brief clearStatusBar Clears the statusbar.
     * \pre Statusbar has been set.
     */
    void clearStatusBar();

    /*!
     * \brief setStatusBar Sets the statusbar so eventhandler can show messages.
     * \param statusbar Pointer to the statusbar.
     */
    void setStatusBar(QStatusBar* statusbar);

private:
    std::shared_ptr<Student::GalaxyMap> galaxymap_;
    std::shared_ptr<Student::Statistics> statistics_;
    std::shared_ptr<Student::Galaxy> galaxy_;
    std::shared_ptr<Student::PlayerShip> playership_;
    std::shared_ptr<Common::IGameRunner> gamerunner_;
    QStatusBar* statusbar_;

    /*!
     * \brief robShip Rob a ship; awards points and credits and deletes the ship.
     * \param ship The poor victim.
     * \pre Statistics has been set.
     */
    void robShip(std::shared_ptr<Common::Ship> ship);
};
}

#endif // EVENTHANDLER_HH
