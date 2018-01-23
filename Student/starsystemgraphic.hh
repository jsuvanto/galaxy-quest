#ifndef STARSYSTEMGRAPHIC_HH
#define STARSYSTEMGRAPHIC_HH

#include "starsystem.hh"
#include "eventhandler.hh"
#include <QGraphicsEllipseItem>

namespace Student {

/*!
 * \brief The StarSystemGraphic class a clickable graphic element to represent star systems as dots in the galaxy map view.
 */
class StarSystemGraphic: public QGraphicsEllipseItem
{
public:

    StarSystemGraphic();
    ~StarSystemGraphic();

    /*!
     * \brief StarSystemGraphic Draw a star system in the origin of the galaxy map.
     * \param system The star system.
     * \param handler Event handler to which pass mouse events.
     */
    StarSystemGraphic(std::shared_ptr<Common::StarSystem> system, std::shared_ptr<Student::EventHandler> handler);


    /*!
     * \brief mousePressEvent Triggered when user clicks the star system.
     * \param event The created event.
     */
    void mousePressEvent(QGraphicsSceneMouseEvent* event);

    /*!
     * \brief hoverEnterEvent Triggered when user moves the mouse over a star system.
     * \param event The created event.
     */
    void hoverEnterEvent(QGraphicsSceneHoverEvent* event);

    /*!
     * \brief hoverLeaveEvent Triggered when user moves the mouse away from the star system.
     * \param event The event.
     */
    void hoverLeaveEvent(QGraphicsSceneHoverEvent* event);

private:
    std::shared_ptr<Student::EventHandler> eventhandler_;
    std::shared_ptr<Common::StarSystem> system_;    

};
}

#endif // STARSYSTEMGRAPHIC_HH
