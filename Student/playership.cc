#include "playership.hh"
#include "shipengine.hh"
#include "iaction.hh"
#include "moveaction.hh"
#include "repairaction.hh"
#include "unloadcargo.hh"
#include "loadcargo.hh"
#include "distressaction.hh"
#include "chargeaction.hh"

#include <memory>

namespace Student {


PlayerShip::PlayerShip(std::shared_ptr<Common::ShipEngine> engine,
                       std::shared_ptr<Common::StarSystem> initialLocation,
                       std::shared_ptr<Common::IEventHandler> events)
    : Ship(engine, initialLocation, events)
{}

bool PlayerShip::canDecideAction()
{
    return !(isAbandoned() || currentAction_);
}

bool PlayerShip::decideAction()
{
   return false;
}

bool PlayerShip::tryMoveTo(std::shared_ptr<Common::StarSystem> dest)
{
    if (!canDecideAction())
        return false;

    if (!engine_)
        return true;

    auto systems = engine_->getValidDestinations(location_);
    if (systems.size() < 1)
        return false;

    auto ma = std::make_shared<Common::MoveAction>(shared_from_this(), dest, events_);
    if (ma->canDo()) {
        currentAction_ = ma;
        return true;
    }

    return false;
}

std::shared_ptr<Common::IAction> PlayerShip::getAction() const
{
    return currentAction_;
}

}
