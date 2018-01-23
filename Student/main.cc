#include "playership.hh"
#include "galaxy.hh"
#include "initialize.hh"
#include "igamerunner.hh"
#include "utility.hh"
#include "eventhandler.hh"
#include "mainwindow.hh"
#include "statistics.hh"
#include "galaxymap.hh"
#include "warpdriveplusplus.hh"
#include "ioexception.hh"
#include "formatexception.hh"

#include <QMessageBox>
#include <QApplication>
#include <memory>
#include <time.h>
#include <iostream>
#include <string>
#include <QGraphicsScene>

int main(int argc, char *argv[]) {

    QApplication a(argc, argv);

    std::shared_ptr<Student::Galaxy> galaxy = std::make_shared<Student::Galaxy>();
    std::shared_ptr<Student::EventHandler> handler = std::make_shared<Student::EventHandler>(galaxy);
    std::shared_ptr<Common::IGameRunner> gameRunner;
    Common::utilityInit(time(NULL));

    // Handle errors
    try {
        gameRunner = Common::getGameRunner(galaxy, handler);
    } catch (const Common::IoException &e) {
        QMessageBox::critical(nullptr, "IO Exception", e.msg().c_str());
        return -1;
    } catch (const Common::FormatException &e) {
        QMessageBox::critical(nullptr, "JSON Format Exception", e.msg().c_str());
        return -2;
    }

    // Make a new statistics object and a pointer to it.
    std::shared_ptr<Student::Statistics> stats = std::make_shared<Student::Statistics>();

    // Make a scene to hold the galaxy map
    std::shared_ptr<Student::GalaxyMap> galaxymap = std::make_shared<Student::GalaxyMap>();
    galaxymap->setEventHandler(handler);


    // link the statistics to the event handler.
    handler->setStatsPointer(stats);
    handler->setGalaxyMap(galaxymap);
    handler->setGameRunner(gameRunner);

    // Create a main window
    MainWindow mainwindow;
    mainwindow.show();
    mainwindow.setStatistics(stats);
    mainwindow.setEventHandler(handler);
    mainwindow.setGameRunner(gameRunner);

    galaxymap->drawStarSystems(galaxy->getStarSystems());
    mainwindow.setGalaxyMap(galaxymap);

    gameRunner->spawnShips(10);

    auto engine = std::make_shared<Student::WarpDrivePlusPlus>(galaxy);
    mainwindow.setPlayerEngine(engine);

    auto targetSystem = galaxy->getRandomSystem();
    //auto coords = targetSystem->getCoordinates();
    //std::cout << "creating playership in " << targetSystem->getName() << ": (" << coords.x << ", " << coords.y << ")" << std::endl;
    std::shared_ptr<Student::PlayerShip> playerShip(new Student::PlayerShip(engine, targetSystem, handler));
    galaxy->addShip(playerShip);
    handler->setPlayerShip(playerShip);
    playerShip->setName("Player ship");
    handler->shipSpawned(playerShip);

    mainwindow.setPlayerShip(playerShip);    

    return a.exec();
}
