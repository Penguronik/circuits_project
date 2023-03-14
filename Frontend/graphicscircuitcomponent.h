#ifndef GRAPHICSCIRCUITCOMPONENT_H
#define GRAPHICSCIRCUITCOMPONENT_H

//HEADERS
#include "Backend/circuitcomponent.h"
class GraphicsWire;
class GraphicsPinIn;
class GraphicsPinOut;

//QT
#include <QGraphicsItemGroup>
#include <QPainter>
#include <QList>

class GraphicsCircuitComponent : public QGraphicsItem
{
//    Q_OBJECT If you want to use q object properties, reinclude this and also inherit QGraphicsObject instead
public:

    // Qt Type
    enum{Type = 0b11000000000000000};
    virtual int type() const override { return Type; }

    // Constructors
    explicit GraphicsCircuitComponent(CircuitComponent *circuit, QGraphicsItem *parent = nullptr);

    // Destructor
    ~GraphicsCircuitComponent();

    // Getters
    virtual QRectF boundingRect() const override;
    QPainterPath shape() const override;

    // Public Functions
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    void updateStates();
    void updateWires();
    void run();
    void updatePinColors();


protected:
    void addPinInAtCenterPoint(qreal x, qreal y, int pinIndex);
    void addPinOutAtCenterPoint(qreal x, qreal y, int pinIndex);

    QList<GraphicsPinIn*> pinInList_;
    QList<GraphicsPinOut*> pinOutList_;
    CircuitComponent *circuitComponent_;
    QPainterPath painterPath_;

};

#endif // GRAPHICSCIRCUITCOMPONENT_H
