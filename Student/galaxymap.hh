#ifndef GALAXYMAP_HH
#define GALAXYMAP_HH

namespace Student {
    class GalaxyMap;
}

#include "ship.hh"
#include "starsystem.hh"
#include "eventhandler.hh"


#include <QGraphicsScene>
#include <QGraphicsItem>
#include <memory>

namespace Student {


class GalaxyMap
{
public:

    GalaxyMap();
    ~GalaxyMap();

    /*!
     * \brief setEventHandler Sets the event handler.
     * \param handler Pointer to event handler.
     */
    void setEventHandler(std::shared_ptr<Student::EventHandler> handler);

    /*!
     * \brief drawStarSystems Draws all the star systems in the galaxy map.
     * \param systems A vector containing the star systems.
     * \pre Event handler has been set.
     */
    void drawStarSystems(const Common::StarSystem::StarSystemVector &systems);

    /*!
     * \brief registerShip Assigns a ship with its own graphic representation and draws it on the galaxy map.
     * \param ship Pointer to the ship.
     */
    void registerShip(std::shared_ptr<Common::Ship> ship);

    /*!
     * \brief moveShip Moves a ship's graphic to the ship's new location.
     * \param ship The ship.
     * \param target The ship's new location.
     * \pre The ship has been registered.
     */
    void moveShip(std::shared_ptr<Common::Ship> ship, Common::Point target);

    /*!
     * \brief deleteShip Removes a ship from the galaxy map. Also removes the distress icon if such exists.
     * \param ship The ship.
     * \pre The ship has been registered.
     */
    void deleteShip(std::shared_ptr<Common::Ship> ship);

    /*!
     * \brief distressOn Displays a distress icon for a ship in the galaxy map.
     * \param ship The ship in distress.     
     */
    void distressOn(std::shared_ptr<Common::Ship> ship);

    /*!
     * \brief distressOff Removes the distress icon from the galaxy map.
     * \param ship The ship no longer in distress.
     * \pre The ship already is in distress.
     */
    void distressOff(std::shared_ptr<Common::Ship> ship);

    /*!
     * \brief getScene Returns the pointer to the galaxy map scene.
     * \return A pointer.
     */
    QGraphicsScene* getScene();

    /*!
     * \brief getScale Get the galaxy map's drawing scale.
     * \return The scale.
     */
    int getScale() const;

    /*!
     * \brief getShipLocation Get ship location in graphics scene coordinates.
     * \param ship The ship.
     * \return Ship's location in the graphics scene.
     */
    QPointF getShipLocation(std::shared_ptr<Common::Ship> ship);

private:

    /*!
     * \brief galaxymapscene_ Holds the galaxy map.
     */
    QGraphicsScene galaxymapscene_;

    /*!
     * \brief ship_graphics Stores ships graphics.
     */
    std::map<std::shared_ptr<Common::Ship>, QGraphicsEllipseItem* > ship_graphics_;

    /*!
     * \brief ships_in_distress_ Stores ships in distress and their icons.
     */
    std::map<std::shared_ptr<Common::Ship>, QGraphicsSimpleTextItem* > ships_in_distress_;

    /*!
     * \brief SCALE_ The drawing scale of the galaxy map
     */
    const int SCALE_ = 20;

    /*!
     * \brief shipsize_ Size of the ship graphic in pixels.
     */
    const qreal shipsize_ = 10;

    /*!
     * \brief ship_brush_ Brush for drawing ships.
     */
    QBrush ship_brush_ = QBrush(Qt::red);

    /*!
     * \brief ship_pen_ Pen for drawing ships.
     */
    QPen ship_pen_ = QPen(ship_brush_, 3);

    /*!
     * \brief playership_brush_ Brush for drawing player ship.
     */
    QBrush playership_brush_ = QBrush(Qt::green);

    /*!
     * \brief playership_pen_ Pen for drawing player ship.
     */
    QPen playership_pen_ = QPen(playership_brush_, 4);

    /*!
     * \brief star_brush_ Brush for drawing star systems.
     */
    QBrush star_brush_ = QBrush(Qt::white);

    /*!
     * \brief eventhandler_ Event handler
     */
    std::shared_ptr<Student::EventHandler> eventhandler_;

};


}

#endif // GALAXYMAP_HH
