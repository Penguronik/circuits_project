#ifndef GRAPHICSCIRCUITCOMPONENT_H
#define GRAPHICSCIRCUITCOMPONENT_H

//HEADERS
#include "Backend/circuitcomponent.h"
class GraphicsWire;
#include "body.h"
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
    virtual QRectF boundingRect() const override; // get rid of these overridden functions and make GraphicsCircuitComponent abstract/"virtual"
    virtual QPainterPath shape() const override;

    // Public Functions
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
    void generateInPins();
    void generateOutPins();
    void updateStates();
    void updateWires();
    void run();
    void updatePinColors();


protected:
    Body *body_;
    QList<GraphicsPinIn*> pinInList_;
    QList<GraphicsPinOut*> pinOutList_;
    CircuitComponent *circuitComponent_;

};

#endif // GRAPHICSCIRCUITCOMPONENT_H
