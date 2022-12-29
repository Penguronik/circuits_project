//HEADERS
#include "pin.h"

//QT
#include <QtGui/qbrush.h>

Pin::Pin(qreal x, qreal y, qreal width, qreal height, QGraphicsItem *parent):
    QGraphicsEllipseItem(x, y, width, height, parent)
{
    setAcceptHoverEvents(true);
    setBrush(QBrush{Qt::green});
}

Pin::Pin(const QRectF &rect, QGraphicsItem *parent):
    QGraphicsEllipseItem(rect, parent)
{
    setAcceptHoverEvents(true);
    setBrush(QBrush{Qt::green});
}

Pin::Pin(QGraphicsItem *parent):
    QGraphicsEllipseItem(parent)
{
    setAcceptHoverEvents(true);
    setBrush(QBrush{Qt::green});
}

void Pin::hoverEnterEvent(QGraphicsSceneHoverEvent *event) {
    QBrush tempBrush = brush();
    tempBrush.setColor(QColor{Qt::green}.lighter(150));
    setBrush(tempBrush);
    update();
}

void Pin::hoverLeaveEvent(QGraphicsSceneHoverEvent *event) {
    QBrush tempBrush = brush();
    tempBrush.setColor(Qt::green);
    setBrush(tempBrush);
    update();
}
