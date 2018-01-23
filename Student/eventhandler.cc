#include "galaxy.hh"
#include "eventhandler.hh"
#include "point.hh"
#include "starsystem.hh"
#include "ship.hh"
#include "mainwindow.hh"
#include "playership.hh"


#include <iostream>
#include <cassert>
#include <QStatusBar>
#include <QMessageBox>


Student::EventHandler::EventHandler(std::shared_ptr<Student::Galaxy> galaxy)
    : galaxy_(galaxy)
{}

Student::EventHandler::~EventHandler() {

}

void Student::EventHandler::shipSpawned(std::shared_ptr<Common::Ship> ship) {
    assert(galaxymap_);
    //std::cout << ship->getName() << " is at " << ship->getLocation()->getName() <<  std::endl; //testing
    galaxymap_->registerShip(ship);
}

void Student::EventHandler::shipRemoved(std::shared_ptr<Common::Ship> ship) {
    assert(galaxymap_);
    assert(gamerunner_);
    // Spawn more ships if they end.
    galaxymap_->deleteShip(ship);
    if (galaxy_->getShips()->size() < 2) {
        gamerunner_->spawnShips(10);
    }
}

void Student::EventHandler::shipRelocated(std::shared_ptr<Common::Ship> ship, std::shared_ptr<Common::StarSystem> starSystem) {
    assert(playership_);
    if (starSystem == nullptr) {
        //std::cout << ship->getName() << " arrived to " << ship->getLocation()->getName() << std::endl;

        // NPC arrives to the player's star system
        if (ship != playership_ && playership_->getLocation() == ship->getLocation()) {
            //std::cout << ship->getName() << " arrived to the same system as player" << std::endl;
            robShip(ship);
        }

        // Player arrives to a star system
        if (ship == playership_) {
            auto ships = galaxy_->getShipsInStarSystem(playership_->getLocation());
            for (auto ship: ships) {
                if (ship != playership_) robShip(ship);
            }
        }
    }
    //else std::cout << ship->getName() << " has left " << starSystem->getName() << std::endl;
}

void Student::EventHandler::shipMoved(std::shared_ptr<Common::Ship> ship, Common::Point /*origin*/, Common::Point target) {
    assert(galaxymap_);
    //std::cout << ship->getName() << " moved from " << origin.toString() << " to " << target.toString() << std::endl; //testing
    galaxymap_->moveShip(ship, target);
}

void Student::EventHandler::exceptionInExecution(std::shared_ptr<Common::Ship> ship, const std::__cxx11::string &msg) {
    QMessageBox msgbox;
    std::string error = ship->getName() + " caused an exception: " + msg;
    msgbox.setText("Exception in execution");
    msgbox.setInformativeText(QString::fromStdString(error));

}

void Student::EventHandler::distressOn(std::shared_ptr<Common::Ship> ship) {
    assert(galaxymap_);
    galaxymap_->distressOn(ship);
}

void Student::EventHandler::distressOff(std::shared_ptr<Common::Ship> ship) {
    assert(galaxymap_);
    galaxymap_->distressOff(ship);
}

void Student::EventHandler::shipAbandoned(std::shared_ptr<Common::Ship> ship) {
    assert(statistics_);
    //std::cout << ship->getName() << " abandoned." << std::endl;
    galaxy_->removeShip(ship);
    statistics_->addLostShip();
    shipRemoved(ship);
}

void Student::EventHandler::setGalaxyMap(std::shared_ptr<Student::GalaxyMap> galaxymap) {    
    galaxymap_ = galaxymap;
    //std::cout << "Galaxy map set in event handler" << std::endl;
}

void Student::EventHandler::setPlayerShip(std::shared_ptr<Student::PlayerShip> playership) {
    playership_ = playership;
}

void Student::EventHandler::starSystemClicked(std::shared_ptr<Common::StarSystem> system){
    assert(statusbar_);
    assert(playership_);
    statusbar_->showMessage(QString::fromStdString(system->getName() + " set as target"), 3000);
    if (!playership_->tryMoveTo(system))
        statusbar_->showMessage("Target system already set!", 3000);
}

void Student::EventHandler::setGameRunner(std::shared_ptr<Common::IGameRunner> gamerunner) {
    gamerunner_ = gamerunner;
}

void Student::EventHandler::showStarSystemInfo(std::shared_ptr<Common::StarSystem> system) {
    assert(statusbar_);
    const std::string econ[] = {"Refinery", "Extraction", "HiTech", "Industrial", "Tourism", "Agriculture", "Service", "Military", "Terraforming", "Colony", "None"};
    std::string statusbartext = system->getName() + ": " + econ[system->getEconomy()] + ", population " + std::to_string(system->getPopulation());
    statusbar_->showMessage(QString::fromStdString(statusbartext));
}

void Student::EventHandler::clearStatusBar() {
    assert(statusbar_);
    statusbar_->clearMessage();
}

void Student::EventHandler::setStatusBar(QStatusBar* statusbar) {
    statusbar_ = statusbar;
}

void Student::EventHandler::robShip(std::shared_ptr<Common::Ship> ship) {
    assert(statistics_);
    //std::cout << ship->getName() << " robbed!" << std::endl;
    statistics_->addCredits(Common::randomMinMax(10,100));
    statistics_->addSavedShip();
    statistics_->addPoints(10);
    galaxy_->removeShip(ship);
    shipRemoved(ship);
}


void Student::EventHandler::setStatsPointer(std::shared_ptr<Student::Statistics> statistics){
    statistics_ = statistics;
}

