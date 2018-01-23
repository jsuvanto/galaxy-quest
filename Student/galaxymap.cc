#include "galaxymap.hh"
#include "playership.hh"
#include "starsystemgraphic.hh"
#include "starsystem.hh"
#include "eventhandler.hh"

#include <iostream>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <cassert>


Student::GalaxyMap::GalaxyMap() {
    galaxymapscene_.setSceneRect(SCALE_ * -30, SCALE_ * -30, SCALE_ * 60, SCALE_ * 60); // Set the maximum bounds of the scene.
}

Student::GalaxyMap::~GalaxyMap() {

}

void Student::GalaxyMap::setEventHandler(std::shared_ptr<Student::EventHandler> handler) {
    eventhandler_ = handler;
}

void Student::GalaxyMap::drawStarSystems(const Common::StarSystem::StarSystemVector &systems) {

    assert(eventhandler_);

    //std::cout << std::endl << "Star systems:" << std::endl;

    for (auto system: systems) {        
        int xcoord = system->getCoordinates().x * SCALE_;
        int ycoord = system->getCoordinates().y * SCALE_;

        Student::StarSystemGraphic* starsystemg = new Student::StarSystemGraphic(system, eventhandler_);
        starsystemg->setPos(xcoord, ycoord);
        starsystemg->setBrush(star_brush_);
        starsystemg->setPen(QPen());
        starsystemg->setAcceptHoverEvents(true);

        galaxymapscene_.addItem(starsystemg);

        QGraphicsSimpleTextItem* text = galaxymapscene_.addSimpleText(QString::fromStdString(system->getName()), QFont());
        text->setBrush(star_brush_);
        text->setPos(xcoord, ycoord+10);

        //std::cout << system->getName() << " is at location: " <<  coords.toString() << " and has population of " << system->getPopulation() << std::endl; // Debug info
    }
}

void Student::GalaxyMap::registerShip(std::shared_ptr<Common::Ship> ship) {    
    Common::Point coords = ship->getLocation()->getCoordinates();
    qreal xcoord = coords.x * SCALE_;
    qreal ycoord = coords.y * SCALE_;

    bool is_playership = dynamic_cast<Student::PlayerShip *>(ship.get()) != nullptr;
    const QPen &pen = is_playership ? playership_pen_ : QPen(QBrush(QColor(255, Common::randomMinMax(0, 255), Common::randomMinMax(0,255))), 2);

    QGraphicsEllipseItem* ship_graphic(galaxymapscene_.addEllipse(0, 0, shipsize_, shipsize_, pen, QBrush()));
    ship_graphic->setPos(xcoord, ycoord);
    ship_graphics_[ship] = ship_graphic;
}

void Student::GalaxyMap::moveShip(std::shared_ptr<Common::Ship> ship, Common::Point target) {
    assert(ship_graphics_[ship]);
    qreal xcoord = target.x * SCALE_;
    qreal ycoord = target.y * SCALE_;
    ship_graphics_[ship]->setPos(xcoord, ycoord);
}

void Student::GalaxyMap::deleteShip(std::shared_ptr<Common::Ship> ship) {
    assert(ship_graphics_[ship]);
    galaxymapscene_.removeItem(ship_graphics_[ship]);
    delete ship_graphics_[ship];
    ship_graphics_.erase(ship);
    if (ships_in_distress_[ship]) distressOff(ship);
}

void Student::GalaxyMap::distressOn(std::shared_ptr<Common::Ship> ship) {    
    Common::Point coords = ship->getLocation()->getCoordinates();
    qreal xcoord = coords.x * SCALE_;
    qreal ycoord = coords.y * SCALE_;

    QGraphicsSimpleTextItem* distress_icon(galaxymapscene_.addSimpleText("!", QFont()));    
    ships_in_distress_[ship] = distress_icon;
    distress_icon->setBrush(ship_brush_);
    distress_icon->setPos(xcoord+5, ycoord-20);
    //std::cout << ship->getName() << " in " << ship->getLocation()->getName() << " (" << ship->getLocation()->getCoordinates().toString() << ") is in distress" << std::endl;
}

void Student::GalaxyMap::distressOff(std::shared_ptr<Common::Ship> ship) {
    assert(ships_in_distress_[ship]);
    galaxymapscene_.removeItem(ships_in_distress_[ship]);
    delete ships_in_distress_[ship];
    ships_in_distress_.erase(ship);
}

QGraphicsScene* Student::GalaxyMap::getScene() {
    return &galaxymapscene_;
}

int Student::GalaxyMap::getScale() const {
    return SCALE_;
}

QPointF Student::GalaxyMap::getShipLocation(std::shared_ptr<Common::Ship> ship) {
    return ship_graphics_[ship]->pos();
}

