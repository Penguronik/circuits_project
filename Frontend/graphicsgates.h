#ifndef GRAPHICSGATES_H
#define GRAPHICSGATES_H

#include "Backend/gates.cpp"
#include "graphicscircuitcomponent.h"

class GraphicsANDGate : public GraphicsCircuitComponent
{
public:

    // Qt Type
    enum{Type = 0b11000000000000001};
    int type() const override { return Type; }

    // Constructor
    GraphicsANDGate(ANDGate *circuitComponent = new ANDGate{}, QGraphicsItem *parent = nullptr);

private:
    void generatePins();
};

class GraphicsORGate : public GraphicsCircuitComponent
{
public:

    // Qt Type
    enum{Type = 0b11000000000000010};
    int type() const override { return Type; }

    GraphicsORGate(ORGate *circuitComponent = new ORGate{}, QGraphicsItem *parent = nullptr);

private:
    void generatePins();
};

class GraphicsNOTGate : public GraphicsCircuitComponent
{
public:

    // Qt Type
    enum{Type = 0b11000000000000011};
    int type() const override { return Type; }

    GraphicsNOTGate(NOTGate *circuitComponent = new NOTGate{}, QGraphicsItem *parent = nullptr);

private:
    void generatePins();
};

class GraphicsXORGate : public GraphicsCircuitComponent
{
public:

    // Qt Type
    enum{Type = 0b11000000000000111};
    int type() const override { return Type; }

    GraphicsXORGate(XORGate *circuitComponent = new XORGate{}, QGraphicsItem *parent = nullptr);

    // Getters
    virtual QRectF boundingRect() const override;
    QPainterPath shape() const override;

    // Public Functions
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

private:
    void generatePins();
    QPainterPath xorArc;
    int xorDist;
};

#endif // GRAPHICSGATES_H
