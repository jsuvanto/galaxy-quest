#include "galaxy.hh"
#include "objectnotfoundexception.hh"
#include "stateexception.hh"
#include <algorithm>
#include <memory>
#include <string>
#include <random>

static Common::StarSystem::StarSystemVector::iterator findMatchingStarSystem(
Common::StarSystem::StarSystemVector &v,
std::shared_ptr<Common::StarSystem> system)
{
    auto it = v.begin();
    for (; it != v.end(); ++it)
        if ((*it)->getName()         == system->getName() ||
            (*it)->getId()           == system->getId() ||
            (*it)->getCoordinates()  == system->getCoordinates())
            
            break;
    
    return it;
}

Student::Galaxy::Galaxy()
{

}

Student::Galaxy::~Galaxy()
{

}

void Student::Galaxy::addShip(std::shared_ptr<Common::Ship> ship)
{
    if (std::find(ships.begin(), ships.end(), ship) != ships.end())
        throw Common::StateException("Ship already in galaxy!");

    ships.push_back(ship);
}

void Student::Galaxy::removeShip(std::shared_ptr<Common::Ship> ship)
{
    auto it = std::find(ships.begin(), ships.end(), ship);
    if (it == ships.end())
        throw Common::ObjectNotFoundException("No such ship in galaxy!");
    
    ships.erase(it);
}

void Student::Galaxy::addStarSystem(std::shared_ptr<Common::StarSystem> starSystem)
{
    if (findMatchingStarSystem(starSystems, starSystem) != starSystems.end())
        throw Common::StateException("Star system already in galaxy!");

    starSystems.push_back(starSystem);
}

std::shared_ptr<Common::IGalaxy::ShipVector> Student::Galaxy::getShips()
{
    return std::make_shared<Common::IGalaxy::ShipVector>(ships);
}

Common::StarSystem::StarSystemVector Student::Galaxy::getSystemsInRange(std::shared_ptr<Common::StarSystem> origin, int range)
{
    Common::Point originCoords = origin->getCoordinates();
    Common::StarSystem::StarSystemVector result;

    if (std::find(starSystems.begin(), starSystems.end(), origin) == starSystems.end())
        throw Common::ObjectNotFoundException("No such star system in galaxy!");

    for (auto it = starSystems.begin(); it != starSystems.end(); ++it) {
        if (*it == origin)
            continue;

        Common::Point targetCoords = (*it)->getCoordinates();
        if (Common::distance(originCoords.x, originCoords.y, targetCoords.x, targetCoords.y) <= range)
            result.push_back(*it);
    }
    
    return result;
}

std::shared_ptr<Common::StarSystem> Student::Galaxy::getRandomSystem()
{
    size_t numStarSystems = starSystems.size();
    if (numStarSystems == 0)
        throw Common::ObjectNotFoundException("No star systems in galaxy!");

    auto it = starSystems.begin();
    it += Common::randomMinMax(0, numStarSystems - 1);
    return *it;
}

Common::IGalaxy::ShipVector Student::Galaxy::getShipsInStarSystem(std::__cxx11::string name)
{
    auto system = getStarSystemByName(name);
    return getShipsInStarSystem(system);
}

Common::IGalaxy::ShipVector Student::Galaxy::getShipsInStarSystem(std::shared_ptr<Common::StarSystem> system)
{
    Common::IGalaxy::ShipVector result;

    for (auto it = ships.begin(); it != ships.end(); ++it)
        if ((*it)->getLocation() == system)
            result.push_back(*it);

    return result;
}

std::vector<std::__cxx11::string> Student::Galaxy::getSystemNames()
{
    std::vector<std::__cxx11::string> result;
    for (auto it = starSystems.begin(); it != starSystems.end(); ++it)
        result.push_back((*it)->getName());

    return result;
}

std::shared_ptr<Common::StarSystem> Student::Galaxy::getStarSystemByName(std::__cxx11::string name)
{
    for (auto it = starSystems.begin(); it != starSystems.end(); ++it)
        if ((*it)->getName() == name)
            return *it;

    throw Common::ObjectNotFoundException("No such star system " + name);
}

std::shared_ptr<Common::StarSystem> Student::Galaxy::getStarSystemById(unsigned id)
{
    for (auto it = starSystems.begin(); it != starSystems.end(); ++it)
        if ((*it)->getId() == id)
            return *it;

    throw Common::ObjectNotFoundException("No star system with id " + std::to_string(id));

}

Common::StarSystem::StarSystemVector Student::Galaxy::getStarSystems(){
    return starSystems;
}

