#include "graphicscomponents.h"

GraphicsButtonComponent::GraphicsButtonComponent(ButtonComponent *circuitComponent, QGraphicsItem *parent):
    GraphicsCircuitComponent(circuitComponent, parent),
    buttonPin_{0, 0, 25, 25, this}
{

}

QRectF GraphicsButtonComponent::boundingRect() const {
    return QRectF{0, 0, 52, 52};
}

QPainterPath GraphicsButtonComponent::shape() const {
    QPainterPath path{};
    path.addRect(0, 0, 50, 50);
    return path;
}

void GraphicsButtonComponent::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    QPainterPath path{shape()};
    painter->setPen(QPen{Qt::black, 2});
    painter->setBrush(Qt::gray);
    painter->drawPath(path);
}

void GraphicsButtonComponent::setButtonState(bool state) {
    static_cast<ButtonComponent *> (circuitComponent_)->setState(state);
}

GraphicsButtonPin::GraphicsButtonPin(qreal x, qreal y, qreal w, qreal h, QGraphicsItem *parent):
    QGraphicsEllipseItem(0, 0, w, h, parent)
{
    setPos(x, y);
    setBrush(QBrush{Qt::red});
}

void GraphicsButtonPin::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    GraphicsButtonComponent *parentButton = qgraphicsitem_cast<GraphicsButtonComponent *>(parentItem());
    parentButton->setButtonState(true);
}

void GraphicsButtonPin::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    GraphicsButtonComponent *parentButton = qgraphicsitem_cast<GraphicsButtonComponent *>(parentItem());
    parentButton->setButtonState(false);
}

GraphicsCircuitIn::GraphicsCircuitIn(CircuitIn *circuitComponent, QGraphicsItem *parent):
    GraphicsCircuitComponent(circuitComponent, parent)
{

}

GraphicsCircuitIn::GraphicsCircuitIn(int inSize, QGraphicsItem *parent):
    GraphicsCircuitIn(new CircuitIn{inSize}, parent)
{

}

QRectF GraphicsCircuitIn::boundingRect() const {
    return QRectF{0, 0, 22, 52};
}

QPainterPath GraphicsCircuitIn::shape() const {
    QPainterPath path{};
    path.addRoundedRect(0, 0, 20, 50, 2, 2);
    return path;
}

void GraphicsCircuitIn::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    QPainterPath path{shape()};
    painter->setPen(QPen{Qt::black, 2});
    painter->setBrush(Qt::gray);
    painter->drawPath(path);
}

GraphicsCircuitOut::GraphicsCircuitOut(CircuitOut *circuitComponent, QGraphicsItem *parent):
    GraphicsCircuitComponent(circuitComponent, parent)
{

}

GraphicsCircuitOut::GraphicsCircuitOut(int outSize, QGraphicsItem *parent):
    GraphicsCircuitOut(new CircuitOut{outSize}, parent)
{

}

QRectF GraphicsCircuitOut::boundingRect() const {
    return QRectF{0, 0, 22, 52};
}

QPainterPath GraphicsCircuitOut::shape() const {
    QPainterPath path{};
    path.addRoundedRect(0, 0, 20, 50, 2, 2);
    return path;
}

void GraphicsCircuitOut::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    QPainterPath path{shape()};
    painter->setPen(QPen{Qt::black, 2});
    painter->setBrush(Qt::gray);
    painter->drawPath(path);
}

void GraphicsCircuitIn::run(bool input[]) {
    static_cast<CircuitIn *> (circuitComponent_)->run(input);
}
