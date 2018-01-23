#ifndef PLAYERSHIP_HH
#define PLAYERSHIP_HH

#include "ship.hh"
#include "shipengine.hh"
#include "starsystem.hh"
#include "ieventhandler.hh"
#include <memory>

namespace Student {

class PlayerShip : public Common::Ship
{
public:
    /*!
     * \brief PlayerShip Construct a player ship
     * \param engine Engine for the ship
     * \param initialLocation initial location
     * \param events pointer to an event handler
     */
    PlayerShip(std::shared_ptr<Common::ShipEngine> engine,
               std::shared_ptr<Common::StarSystem> initialLocation,
               std::shared_ptr<Common::IEventHandler> events = nullptr);

    /*!
     * \brief decideAction Denies gamerunner access to control the player ship.
     * \return Always false.
     */
    bool decideAction();

    virtual std::shared_ptr<Common::IAction> getAction() const;

    /*!
     * \brief tryMoveTo tries to move to another star system
     * \param dest target to move into
     * \return true on success, false on failure
     */
    bool tryMoveTo(std::shared_ptr<Common::StarSystem> dest);

private:
    /*!
     * \brief canDecideAction determine if we can act (such as move etc)
     * \return true if we can
     */
    bool canDecideAction();
};

}

#endif
