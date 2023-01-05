//UTIL
#include "constants.h"
#include <iostream> //remove all iostreams at the end

//HEADERS
#include "componentcontainer.h"
#include "body.h"

//QT
#include <QGraphicsView>
#include <QKeyEvent>

ComponentContainer::ComponentContainer(Circuit *circuit, QGraphicsItem *parent): //Need to come up with a new name that isnt component or circuit, circuit is too general and does not represent a circuit's component but CircuitComponent feels too long..., once you find it, consider renaming pin and body with the prefix of it such as circuitBody and circuitPin
    QGraphicsItem{parent},
    body_{new Body{0, 0, 50, 30, this}}, //A RENAME IS DEFINITELY NECESSARY VERY SOON
    statePinList_{new QList<Pin*>{}}, //consider making the pin lists not dynamically allocated
    outPinList_{new QList<Pin*>{}},
    circuit_{circuit}
{
    generateStatePins();
    generateOutPins();
    setFlag(QGraphicsItem::ItemIsMovable);
    std::cout << body_ << "<- body address";
}

QRectF ComponentContainer::boundingRect() const{
    return body_->boundingRect();
}

void ComponentContainer::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
    //Empty paint, container item
}

QPainterPath ComponentContainer::shape() const {
    return body_->shape();
}

void ComponentContainer::generateStatePins() {
    qreal interval {body_->boundingRect().height()/circuit_->stateSize()};
    QPointF topLeft {body_->boundingRect().topLeft()};
    topLeft.setY(topLeft.y() + interval/2 - constant::PIN_DIAMETER/2);
    topLeft.setX(topLeft.x() - constant::PIN_DIAMETER/2);
    for (int i {0}; i < circuit_->stateSize(); i++) {
        statePinList_->append(new Pin{topLeft.x(), topLeft.y() + interval*i, constant::PIN_DIAMETER, constant::PIN_DIAMETER, Pin::State, this});
    }
}

void ComponentContainer::generateOutPins() {
    qreal interval {body_->boundingRect().height()/circuit_->outSize()};
    QPointF topRight {body_->boundingRect().topRight()};
    topRight.setY(topRight.y() + interval/2 - constant::PIN_DIAMETER/2);
    topRight.setX(topRight.x() - constant::PIN_DIAMETER/2);
    for (int i {0}; i < circuit_->outSize(); i++) {
        outPinList_->append(new Pin{topRight.x(), topRight.y() + interval*i, constant::PIN_DIAMETER, constant::PIN_DIAMETER, Pin::Out, this});
    }
}
