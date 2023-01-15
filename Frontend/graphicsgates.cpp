#include "graphicsgates.h"

GraphicsANDGate::GraphicsANDGate(CircuitComponent *circuitComponent, QGraphicsItem *parent):
    GraphicsCircuitComponent(circuitComponent, parent)
{

}

QRectF GraphicsANDGate::boundingRect() const {
    return QRectF{0, 0, 52, 32};
}

QPainterPath GraphicsANDGate::shape() const {
    QPainterPath path{};
    path.lineTo(30, 0);
    path.arcTo(30, 0, 20, 30, 90, -180);
    path.lineTo(0, 30);
    path.closeSubpath();
    return path;
}

void GraphicsANDGate::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    QPainterPath path{shape()};
    painter->setPen(QPen{Qt::black, 2});
    painter->setBrush(Qt::gray);
    painter->drawPath(path);
}

GraphicsORGate::GraphicsORGate(CircuitComponent *circuitComponent, QGraphicsItem *parent):
    GraphicsCircuitComponent(circuitComponent, parent)
{

}

QRectF GraphicsORGate::boundingRect() const {
    return QRectF{0, 0, 52, 32};
}

QPainterPath GraphicsORGate::shape() const {
    QPainterPath path{};
    path.lineTo(16, 0);
    path.arcTo(16-40, 0, 2*40, 2*40, 90, -50);
    path.arcTo(16-40, -10-40, 2*40, 2*40, -40, -50);
    path.lineTo(0, 30);
    path.arcTo(-56, 30/2-30, 30*2, 30*2, -30, 60);
    path.closeSubpath();
    return path;
}

void GraphicsORGate::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    QPainterPath path{shape()};
    painter->setPen(QPen{Qt::black, 2});
    painter->setBrush(Qt::gray);
    painter->drawPath(path);
}

GraphicsNOTGate::GraphicsNOTGate(CircuitComponent *circuitComponent, QGraphicsItem *parent):
    GraphicsCircuitComponent(circuitComponent, parent)
{

}

QRectF GraphicsNOTGate::boundingRect() const {
    return QRectF{0, 0, 52, 32};
}

QPainterPath GraphicsNOTGate::shape() const {
    QPainterPath path{};
    path.lineTo(50, 15);
    path.lineTo(0, 30);
    path.closeSubpath();
    return path;
}

void GraphicsNOTGate::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    QPainterPath path{shape()};
    painter->setPen(QPen{Qt::black, 2});
    painter->setBrush(Qt::gray);
    painter->drawPath(path);
}
