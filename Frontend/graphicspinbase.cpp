//HEADERS
#include "graphicspinbase.h"
#include "wire.h"

//QT
#include <QtGui/qbrush.h>
#include <QGraphicsSceneMouseEvent>
#include <QRect>
#include <QGraphicsView>

#include <iostream>

GraphicsPinBase::GraphicsPinBase(qreal x, qreal y, qreal width, qreal height, Role role, PinBase *pin, int index, QGraphicsItem *parent):
    QGraphicsEllipseItem{0, 0, width, height, parent}, // Original rectangle is set to 0, 0 in order to use pos() instead of boundingrect() to follow position
    role_{role}, // Remove role system and use QT type function instead
    wireList_{},
    index_{index},
    pin_{pin}
{
    setPos(x, y);
    setAcceptHoverEvents(true);
    setFlag(QGraphicsItem::ItemSendsScenePositionChanges);
    setBrush(QBrush{Qt::green});
    setTransformOriginPoint(0,0);
    std::cout << "pin scene x: " << scenePos().x() << std::endl << "pin scene y: " << scenePos().y() << std::endl;
    std::cout << "pin local x: " << pos().x() << std::endl << "pin local y: " << pos().y() << std::endl;
    std::cout << "bouunding rect x: " << mapToScene(boundingRect().center()).x() << "bouunding rect y: " << mapToScene(boundingRect().center()).y() << std::endl;
}

GraphicsPinBase::GraphicsPinBase(const QRectF &rect, Role role, PinBase *pin, int index, QGraphicsItem *parent):
    GraphicsPinBase{rect.x(), rect.y(), rect.width(), rect.height(), role, pin, index, parent}
{

}

void GraphicsPinBase::hoverEnterEvent(QGraphicsSceneHoverEvent *event) {
    QBrush tempBrush = brush();
    tempBrush.setColor(QColor{Qt::green}.lighter(150));
    setBrush(tempBrush);
    update();
}

void GraphicsPinBase::hoverLeaveEvent(QGraphicsSceneHoverEvent *event) {
    QBrush tempBrush = brush();
    tempBrush.setColor(Qt::green);
    setBrush(tempBrush);
    update();
}

QVariant GraphicsPinBase::itemChange(QGraphicsItem::GraphicsItemChange change, const QVariant &value) {
    if (change == QGraphicsItem::ItemScenePositionHasChanged) {
        QList<Wire*>::iterator i{};
        for (i = wireList_.begin(); i != wireList_.end(); ++i) {
            QLineF lineShape{(*i)->line()};
            if( role() == GraphicsPinBase::State) {
                lineShape.setP1(sceneBoundingRect().center());
            }
            else if ( role() == GraphicsPinBase::Out) {
                lineShape.setP2(sceneBoundingRect().center());
            }
            (*i)->setLine(lineShape);
        }
    }

    return QGraphicsItem::itemChange(change, value);
}

GraphicsPinBase::Role GraphicsPinBase::role() const
{
    return role_;
}

void GraphicsPinBase::setRole(GraphicsPinBase::Role role)
{
    role_ = role;
}

void GraphicsPinBase::addWire(Wire *wire) {
    wireList_.append(wire);
}

void GraphicsPinBase::removeWire(Wire *wire) {
    wireList_.removeOne(wire);
}

int GraphicsPinBase::index() const
{
    return index_;
}

void GraphicsPinBase::setIndex(int index)
{
    index_ = index;
}

PinBase *GraphicsPinBase::pin() const
{
    return pin_;
}

void GraphicsPinBase::setPin(PinBase *pin)
{
    pin_ = pin;
}
