#ifndef BODY_H
#define BODY_H

#include <QGraphicsRectItem>

class Body : public QGraphicsRectItem
{
public:
    Body(qreal x, qreal y, qreal width, qreal height, QGraphicsItem *parent = nullptr);
//    virtual QRectF boundingRect() const override;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    virtual QPainterPath shape() const override;
};

#endif // BODY_H
