#include "graphicspinin.h"

GraphicsPinIn::GraphicsPinIn(qreal x, qreal y, qreal width, qreal height, PinIn *pin, int index, QGraphicsItem *parent):
    GraphicsPinBase{x, y, width, height, index, parent},
    pin_{pin}
{
    setFlag(QGraphicsItem::ItemSendsScenePositionChanges);
}

PinIn *GraphicsPinIn::pin() const
{
    return pin_;
}

bool GraphicsPinIn::state() const{
    return pin()->state();
}

QVariant GraphicsPinIn::itemChange(QGraphicsItem::GraphicsItemChange change, const QVariant &value) {
    if (change == QGraphicsItem::ItemScenePositionHasChanged) {
        QList<GraphicsWire*>::iterator i{};
        for (i = wireList_.begin(); i != wireList_.end(); ++i) {
            (*i)->setPinInPosition(sceneBoundingRect().center());
        }
    }

    return QGraphicsItem::itemChange(change, value);
}
