#ifndef GRAPHICSGATES_H
#define GRAPHICSGATES_H

#include "graphicscircuitcomponent.h"

class GraphicsANDGate : public GraphicsCircuitComponent
{
public:
    GraphicsANDGate(CircuitComponent *circuit, QGraphicsItem *parent = nullptr);

    virtual QRectF boundingRect() const override;
    virtual QPainterPath shape() const override;

    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
};

class GraphicsORGate : public GraphicsCircuitComponent
{
public:
    GraphicsORGate(CircuitComponent *circuit, QGraphicsItem *parent = nullptr);

    virtual QRectF boundingRect() const override;
    virtual QPainterPath shape() const override;

    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
};

class GraphicsNOTGate : public GraphicsCircuitComponent
{
public:
    GraphicsNOTGate(CircuitComponent *circuit, QGraphicsItem *parent = nullptr);

    virtual QRectF boundingRect() const override;
    virtual QPainterPath shape() const override;

    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
};

#endif // GRAPHICSGATES_H
