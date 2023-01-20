#include "graphicscomponents.h"
#include <_mingw_mac.h>


GraphicsButtonComponent::GraphicsButtonComponent(ButtonComponent *circuitComponent, QGraphicsItem *parent):
    GraphicsCircuitComponent(circuitComponent, parent),
    buttonPin_{0, 0, 25, 25, this},
    buttonComponent_{circuitComponent}
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
    buttonComponent_->setState(state);
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
