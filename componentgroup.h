#ifndef COMPONENTGROUP_H
#define COMPONENTGROUP_H

#include <QGraphicsItemGroup>
#include <QPainter>
#include <QList>
#include "pin.h"

class ComponentGroup : public QGraphicsItemGroup
{
//    Q_OBJECT If you want to use q object properties, reinclude this and also inherit QGraphicsObject instead
public:
    explicit ComponentGroup(QGraphicsItem * parent = nullptr);

//private:
    int pinCount;
    QGraphicsRectItem *my_rect;
    QList<Pin*> *pinList;
    void generatePins();
};

#endif // COMPONENTGROUP_H
