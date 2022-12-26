#include "pin.h"
#include "qbrush.h"
#include <iostream>

Pin::Pin(qreal x, qreal y, qreal width, qreal height, QGraphicsItem *parent):
    QGraphicsEllipseItem(x, y, width, height, parent)
{
    setAcceptHoverEvents(true);
}

Pin::Pin(const QRectF &rect, QGraphicsItem *parent):
    QGraphicsEllipseItem(rect, parent)
{
    setAcceptHoverEvents(true);
}

Pin::Pin(QGraphicsItem *parent):
    QGraphicsEllipseItem(parent)
{
    setAcceptHoverEvents(true);
}

void Pin::hoverEnterEvent(QGraphicsSceneHoverEvent *event) {
    QBrush pinBrush = brush();
    pinBrush.setColor(pinBrush.color().lighter(150));
    setBrush(QBrush{pinBrush});
    update();
}

void Pin::hoverLeaveEvent(QGraphicsSceneHoverEvent *event) {
    std::cout << "test";
    QBrush pinBrush = brush();
    pinBrush.setColor(pinBrush.color().darker(150));
    setBrush(QBrush{pinBrush});
    update();
}
