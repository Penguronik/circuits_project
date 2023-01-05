#ifndef BODY_H
#define BODY_H

//QT
#include <QGraphicsRectItem>

class Body : public QGraphicsRectItem
{
public:

    // Constructors
    //
    explicit Body(qreal x, qreal y, qreal width, qreal height, QGraphicsItem *parent = nullptr);

    // Getters
    //
//    virtual QRectF boundingRect() const override;
    virtual QPainterPath shape() const override;

    // Public Functions
    //
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

};

#endif // BODY_H
