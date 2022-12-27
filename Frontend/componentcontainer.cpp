//HEADERS
#include "componentcontainer.h"

//QT
#include <QGraphicsView>
#include <QKeyEvent>

ComponentContainer::ComponentContainer(Component *component, QGraphicsItem *parent):
    QGraphicsItem(parent),
    pinCount{component->getOutSize()},
    body{new QGraphicsRectItem{100, 0, 100, 200, this}}, //A RENAME IS DEFINITELY NECESSARY VERY SOON, WILL LIKELY BECOME ITS OWN OBJECT BUT NOT YET SO NO REASON TO OVER COMPLICATE MEANWHILE
    pinList{new QList<Pin*>},
    component_{component}
{ }

QRectF ComponentContainer::boundingRect() const{
    return body->boundingRect();
}

void ComponentContainer::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
    //Empty paint, container item
}

//QPainterPath ComponentContainer::shape() const{
//    QPainterPath shape{};
//}

void ComponentContainer::generatePins() {
    qreal interval {body->boundingRect().height()/pinCount};
    qreal buffer {interval/2};
    QPointF topRight {body->boundingRect().topRight()};
    topRight.setY(topRight.y()+buffer-5); //5 is replaced with the half of circle size
    for (int i {0}; i < pinCount; i++) {
        pinList->append(new Pin{topRight.x()-5, topRight.y() + interval*i, 10, 10, this});
        pinList->at(i)->setBrush(QBrush{Qt::green});
    }
}
