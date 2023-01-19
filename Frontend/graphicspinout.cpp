#include "graphicspinout.h"

GraphicsPinOut::GraphicsPinOut(qreal x, qreal y, qreal width, qreal height, PinOut *pin, int index, QGraphicsItem *parent):
    GraphicsPinBase{x, y, width, height, index, parent},
    pin_{pin}
{
    setFlag(QGraphicsItem::ItemSendsScenePositionChanges);
}

PinOut *GraphicsPinOut::pin() const
{
    return pin_;
}

bool GraphicsPinOut::state() const{
    return pin()->state();
}

QVariant GraphicsPinOut::itemChange(QGraphicsItem::GraphicsItemChange change, const QVariant &value) {
    if (change == QGraphicsItem::ItemScenePositionHasChanged) {
        QList<GraphicsWire*>::iterator i{};
        for (i = wireList_.begin(); i != wireList_.end(); ++i) {
            (*i)->setPinOutPosition(sceneBoundingRect().center());
        }
    }

    return QGraphicsItem::itemChange(change, value);
}
