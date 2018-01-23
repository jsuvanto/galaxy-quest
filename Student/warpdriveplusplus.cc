#include "warpdriveplusplus.hh"
#include <cassert>
#include <cmath>
#include <iostream>

namespace Student {

const int WarpDrivePlusPlus::RANGE = 70;
const int WarpDrivePlusPlus::DISTANCE_PER_MOVEMENT = 6;
const int WarpDrivePlusPlus::MAX_DAMAGE_PER_START = 3;
const int WarpDrivePlusPlus::MIN_DAMAGE_PER_START = 0;
const int WarpDrivePlusPlus::MAX_HEALTH = 18;

WarpDrivePlusPlus::WarpDrivePlusPlus(std::shared_ptr<Student::Galaxy> galaxy): ShipEngine(MAX_HEALTH), galaxy_(galaxy){

}

void WarpDrivePlusPlus::onStart() {
    assert(statusbar_);
    int rand = Common::randomMinMax(MIN_DAMAGE_PER_START, MAX_DAMAGE_PER_START);
    decreaseHealth(rand);
    std::string wroom = "Wroom!";
    for (int i = 1; i < rand; ++i ) wroom += " Wroom!";
    statusbar_->showMessage(QString::fromStdString(wroom), 1000);
}

Common::StarSystem::StarSystemVector WarpDrivePlusPlus::getValidDestinations(std::shared_ptr<Common::StarSystem> source) const {
    assert(source && "WARPENGINEPLUSPLUS: No source given for valid destination query.");

    if (!galaxy_) {
        return Common::StarSystem::StarSystemVector();
    }

    return galaxy_->getSystemsInRange(source, RANGE);
}

bool WarpDrivePlusPlus::isValidTrip(std::shared_ptr<Common::StarSystem> source, std::shared_ptr<Common::StarSystem> destination) const {
    assert(source && "WARPENGINEPLUSPLUS: No source given for valid trip query.");
    assert(destination && "WARPENGINEPLUSPLUS: No destination given for valid trip query.");

    double distance = destination->getCoordinates().distanceTo(source->getCoordinates());

    return distance <= RANGE;
}

int WarpDrivePlusPlus::requiredTurns(std::shared_ptr<Common::StarSystem> source, std::shared_ptr<Common::StarSystem> destination) const {
    assert(DISTANCE_PER_MOVEMENT > 0);

    double distance = destination->getCoordinates().distanceTo(source->getCoordinates());

    double requiredTurns = distance/DISTANCE_PER_MOVEMENT;

    return ceil(requiredTurns);
}

void WarpDrivePlusPlus::setStatusbar(QStatusBar *statusbar) {
    statusbar_ = statusbar;
}


} // Student
