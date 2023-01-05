//HEADERS
#include "pin.h"
#include "wire.h"

//QT
#include <QtGui/qbrush.h>
#include <QGraphicsSceneMouseEvent>
#include <QRect>
#include <QGraphicsView>

#include <iostream>

Pin::Pin(qreal x, qreal y, qreal width, qreal height, Role role, QGraphicsItem *parent):
    QGraphicsEllipseItem{0, 0, width, height, parent}, // Original rectangle is set to 0, 0 in order to use pos() instead of boundingrect() to follow position
    wireList_{},
    role_{role}
{
    id_ = currentId_;
    currentId_++;
    setPos(x, y);
    setAcceptHoverEvents(true);
    setFlag(QGraphicsItem::ItemSendsScenePositionChanges);
    setBrush(QBrush{Qt::green});
    setTransformOriginPoint(0,0);
    std::cout << "pin scene x: " << scenePos().x() << std::endl << "pin scene y: " << scenePos().y() << std::endl;
    std::cout << "pin local x: " << pos().x() << std::endl << "pin local y: " << pos().y() << std::endl;
    std::cout << "bouunding rect x: " << mapToScene(boundingRect().center()).x() << "bouunding rect y: " << mapToScene(boundingRect().center()).y() << std::endl;
}

Pin::Pin(const QRectF &rect, Role role, QGraphicsItem *parent):
    Pin{rect.x(), rect.y(), rect.width(), rect.height(), role, parent}
{

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

QVariant Pin::itemChange(QGraphicsItem::GraphicsItemChange change, const QVariant &value) {
    if (change == QGraphicsItem::ItemScenePositionHasChanged) {
        QList<Wire*>::iterator i{};
        for (i = wireList_.begin(); i != wireList_.end(); ++i) {
            QLineF lineShape{(*i)->line()};
            if( role() == Pin::State) {
                lineShape.setP1(sceneBoundingRect().center());
            }
            else if ( role() == Pin::Out) {
                lineShape.setP2(sceneBoundingRect().center());
            }
            (*i)->setLine(lineShape);
        }
    }

    return QGraphicsItem::itemChange(change, value);
}

Pin::Role Pin::role() const
{
    return role_;
}

void Pin::setRole(Pin::Role role)
{
    role_ = role;
}
