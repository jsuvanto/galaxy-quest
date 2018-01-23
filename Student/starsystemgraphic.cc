#include "starsystemgraphic.hh"
#include "starsystem.hh"
#include "eventhandler.hh"

#include <iostream>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsEllipseItem>

Student::StarSystemGraphic::StarSystemGraphic() {
}

Student::StarSystemGraphic::StarSystemGraphic(std::shared_ptr<Common::StarSystem> system, std::shared_ptr<Student::EventHandler> handler) :
    QGraphicsEllipseItem::QGraphicsEllipseItem(0, 0, 10, 10) {
    system_ = system;
    eventhandler_ = handler;
}

Student::StarSystemGraphic::~StarSystemGraphic() {

}

void Student::StarSystemGraphic::mousePressEvent(QGraphicsSceneMouseEvent* event) {
    if(event->button() == Qt::LeftButton) {
        eventhandler_->starSystemClicked(system_);
    }
    QGraphicsEllipseItem::mousePressEvent(event); // Forward the event to the ellipse
}

void Student::StarSystemGraphic::hoverEnterEvent(QGraphicsSceneHoverEvent* event) {
    eventhandler_->showStarSystemInfo(system_);
    QGraphicsEllipseItem::hoverEnterEvent(event); // Forward the event to the ellipse
}

void Student::StarSystemGraphic::hoverLeaveEvent(QGraphicsSceneHoverEvent* event) {
    eventhandler_->clearStatusBar();
    QGraphicsEllipseItem::hoverLeaveEvent(event); // Forward the event to the ellipse
}
