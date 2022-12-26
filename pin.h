#ifndef PIN_H
#define PIN_H

#include <QGraphicsEllipseItem>

class Pin : public QGraphicsEllipseItem
{
public:
    Pin(qreal x, qreal y, qreal width, qreal height, QGraphicsItem *parent = nullptr);
    Pin(const QRectF &rect, QGraphicsItem *parent = nullptr);
    Pin(QGraphicsItem *parent = nullptr);
    virtual void hoverEnterEvent(QGraphicsSceneHoverEvent *event) override;
    virtual void hoverLeaveEvent(QGraphicsSceneHoverEvent *event) override;
};

#endif // PIN_H
