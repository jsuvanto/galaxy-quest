#ifndef GALAXY_HH
#define GALAXY_HH
#include "igalaxy.hh"
#include "ship.hh"
#include "starsystem.hh"
#include "ieventhandler.hh"
namespace Student {

class Galaxy : public Common::IGalaxy, public std::enable_shared_from_this<Galaxy>
{
public:
    Galaxy();
    ~Galaxy();

    /*!
     * \brief addShip Add a new ship to the galaxy.
     * \param ship The new ship.
     * \exception StateException if ship already exists in the galaxy.
     * \post Exception guarantee: strong
     */
    virtual void addShip(std::shared_ptr<Common::Ship> ship);

    /*!
     * \brief removeShip Remove a ship from the galaxy.
     * \param ship The ship.
     * \exception ObjectNotFoundException if ship does not exist.
     * \post Exception guarantee: strong
     */
    virtual void removeShip(std::shared_ptr<Common::Ship> ship);

    /*!
     * \brief addStarSystem Add a new star system to the galaxy.
     * \param starSystem The new star system.
     * \exception StateException if the galaxy already exists.
     * \post Exception guarantee: strong
     */
    virtual void addStarSystem(std::shared_ptr<Common::StarSystem> starSystem);

    /*!
     * \brief getShips Return the ships in the galaxy.
     * \return Shared pointer to a vector of ships. Vector is empty if no ships exist in the galaxy.
     * \post Exception guarantee: nothrow
     */
    virtual std::shared_ptr<ShipVector> getShips();

    /*!
     * \brief getSystemsInRange Return all star systems at a given range from a star system.
     * \param origin The star system.
     * \param range Distance.
     * \return Vector of star systems within the distance of the given star system, excluding the star system itself. Vector is empty if no star systems exist within the distance.
     * \exception ObjectNotFoundException if the given star system does not exist.
     * \post Exception guarantee: strong
     */
    virtual Common::StarSystem::StarSystemVector getSystemsInRange (std::shared_ptr<Common::StarSystem> origin, int range);

    /*!
     * \brief getRandomSystem Return a random star system.
     * \return A star system.
     * \exception ObjectNotFoundException if the galaxy has no star systems.
     * \post Exception guarantee: strong
     */
    virtual std::shared_ptr<Common::StarSystem> getRandomSystem();

    /*!
     * \brief getShipsInStarSystem Return all ships in a star system.
     * \param name Name of the system.
     * \return A vector of ships in the system. Vector is empty if no ships exist in the system.
     * \exception ObjectNotFoundException if a star system with this name does not exist.
     * \post Exception guarantee: strong
     */
    ShipVector getShipsInStarSystem(std::string name);

    /*!
     * \brief getSystemNames Return a vector of star system names.
     * \return Vector of star system names.
     */
    std::vector<std::string> getSystemNames();

    /*!
     * \brief getStarSystemByName Return a pointer to a system of a given name.
     * \param name Name of the system.
     * \exception ObjectNotFoundException if a system with this name does not exist.
     * \return Shared pointer to the system
     * \post Exception guarantee: strong
     */
    std::shared_ptr<Common::StarSystem> getStarSystemByName(std::string name);

    /*!
     * \brief getStarSystemById Get a star system by id.
     * \param id Id of the star system.
     * \return shared pointer to the star system.
     * \exception ObjectNotFoundException if a star system with that id does not exist.
     * \post Exception guarantee: strong
     */
    std::shared_ptr<Common::StarSystem> getStarSystemById(unsigned id);


    /*!
     * \brief getShipsInStarSystem Gets a list of ships in a star system.
     * \param system Pointer to the system.
     * \return Ships in the system, including the player ship.
     */
    ShipVector getShipsInStarSystem(std::shared_ptr<Common::StarSystem> system);


    /*!
     * \brief getStarSystems Returns all star systems in the galaxy.
     * \return A vector of star systems.
     * \post Excetion guarantee: nothrow
     */
    Common::StarSystem::StarSystemVector getStarSystems();


private:
    Common::StarSystem::StarSystemVector starSystems;
    Common::IGalaxy::ShipVector ships;
};

}//Student

#endif // GALAXY_HH
