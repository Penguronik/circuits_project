#include "graphicspinout.h"

GraphicsPinOut::GraphicsPinOut(qreal x, qreal y, qreal width, qreal height, PinOut *pin, QGraphicsItem *parent):
    GraphicsPinBase{x, y, width, height, parent},
    pin_{pin}
{
    setFlag(QGraphicsItem::ItemSendsScenePositionChanges);
}

GraphicsPinOut::~GraphicsPinOut() {
    pin_ = nullptr; // The expectation is that the backend component will delete the backend pin
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
