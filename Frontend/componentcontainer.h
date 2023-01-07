#ifndef COMPONENTCONTAINER_H
#define COMPONENTCONTAINER_H

//HEADERS
#include "Backend/circuit.h"
#include "body.h"
#include "graphicspin.h"

//QT
#include <QGraphicsItemGroup>
#include <QPainter>
#include <QList>

class ComponentContainer : public QGraphicsItem
{
//    Q_OBJECT If you want to use q object properties, reinclude this and also inherit QGraphicsObject instead
public:

    // Enums
    //
    enum{Type = UserType + 2};

    // Constructors
    //
    explicit ComponentContainer(Circuit *circuit, QGraphicsItem *parent = nullptr);

    // Getters
    //
    virtual QRectF boundingRect() const override;
    virtual QPainterPath shape() const override;
    inline int type() const override { return Type; }

    // Public Functions
    //
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
    void generateStatePins();
    void generateOutPins();

private:
    Body *body_;
    QList<GraphicsPin*> *statePinList_;
    QList<GraphicsPin*> *outPinList_;
    Circuit *circuit_; //rename, but to what?

};

#endif // COMPONENTCONTAINER_H
