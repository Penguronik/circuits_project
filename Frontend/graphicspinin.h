#ifndef GRAPHICSPININ_H
#define GRAPHICSPININ_H

#include "Backend/pinin.h"
#include "graphicspinbase.h"

class GraphicsPinIn : public GraphicsPinBase
{
public:

    // Qt Type
    enum{Type = UserType + 11};
    virtual int type() const override { return Type; }

    GraphicsPinIn(qreal x, qreal y, qreal width, qreal height, PinIn *pin, int index, QGraphicsItem *parent = nullptr);

    virtual QVariant itemChange(QGraphicsItem::GraphicsItemChange change, const QVariant &value) override;

    PinIn *pin() const;

    virtual bool state() const override;


private:
    PinIn *pin_;
};

#endif // GRAPHICSPININ_H
