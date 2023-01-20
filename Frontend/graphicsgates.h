#ifndef GRAPHICSGATES_H
#define GRAPHICSGATES_H

#include "Backend/gates.cpp"
#include "graphicscircuitcomponent.h"

class GraphicsANDGate : public GraphicsCircuitComponent
{
public:

    // Qt Type
    enum{Type = UserType + 1};
    int type() const override { return Type; }

    // Constructor
    GraphicsANDGate(ANDGate *circuitComponent, QGraphicsItem *parent = nullptr);

    virtual QRectF boundingRect() const override;
    virtual QPainterPath shape() const override;

    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
};

class GraphicsORGate : public GraphicsCircuitComponent
{
public:

    // Qt Type
    enum{Type = UserType + 2};
    int type() const override { return Type; }

    GraphicsORGate(ORGate *circuitComponent, QGraphicsItem *parent = nullptr);

    virtual QRectF boundingRect() const override;
    virtual QPainterPath shape() const override;

    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
};

class GraphicsNOTGate : public GraphicsCircuitComponent
{
public:

    // Qt Type
    enum{Type = UserType + 3};
    int type() const override { return Type; }

    GraphicsNOTGate(NOTGate *circuitComponent, QGraphicsItem *parent = nullptr);

    virtual QRectF boundingRect() const override;
    virtual QPainterPath shape() const override;

    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
};

#endif // GRAPHICSGATES_H
