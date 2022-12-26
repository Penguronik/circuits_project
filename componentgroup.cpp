#include "componentgroup.h"
#include <QGraphicsView>
#include <QKeyEvent>

ComponentGroup::ComponentGroup(QGraphicsItem *parent):
    QGraphicsItemGroup(parent),
//    QRectF component_dimensions {100, 0, 80, 100},
    my_rect{new QGraphicsRectItem{100, 0, 100, 200, this}},
    pinList{new QList<Pin*>}
{
    addToGroup(my_rect);
    pinCount = 11;
    generatePins();
    boundingRect().topRight();
    boundingRect().height();
//    pinList->append(new QGraphicsEllipseItem{100, 0, 20, 20, this});
//    addToGroup(pinList->at(0));
    my_rect->setFlag(QGraphicsItem::ItemIsMovable);
}

void ComponentGroup::generatePins() {
    qreal interval {boundingRect().height()/pinCount};
    qreal buffer {interval/2};
    QPointF topRight {boundingRect().topRight()};
    topRight.setY(topRight.y()+buffer-5); //5 is replaced with the half of circle size
    for (int i {0}; i < pinCount; i++) {
        pinList->append(new Pin{topRight.x()-5, topRight.y() + interval*i, 10, 10, this});
        addToGroup(pinList->at(i));
        pinList->at(i)->setBrush(QBrush{Qt::green});
    }
}
