#ifndef COMPONENTCONTAINER_H
#define COMPONENTCONTAINER_H

//HEADERS
#include "Backend/circuit.h"
#include "pin.h"

//QT
#include <QGraphicsItemGroup>
#include <QPainter>
#include <QList>

class ComponentContainer : public QGraphicsItem
{
//    Q_OBJECT If you want to use q object properties, reinclude this and also inherit QGraphicsObject instead
public:
    explicit ComponentContainer(Circuit *circuit, QGraphicsItem *parent = nullptr);
    virtual QRectF boundingRect() const override;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
    virtual QPainterPath shape() const override;
    void generateStatePins();
    void generateOutPins();

private:
    QGraphicsRectItem *body_; //possible change from rectitem to custom item, but that is a future thing and likely may not be necessary
    QList<Pin*> *statePinList_;
    QList<Pin*> *outPinList_;
    Circuit *circuit_; //rename, but to what?

};

#endif // COMPONENTCONTAINER_H
