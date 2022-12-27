#ifndef PIN_H
#define PIN_H

//QT
#include <QGraphicsEllipseItem>

class Pin : public QGraphicsEllipseItem
{
public:
    explicit Pin(qreal x, qreal y, qreal width, qreal height, QGraphicsItem *parent = nullptr);
    explicit Pin(const QRectF &rect, QGraphicsItem *parent = nullptr);
    explicit Pin(QGraphicsItem *parent = nullptr);
    virtual void hoverEnterEvent(QGraphicsSceneHoverEvent *event) override;
    virtual void hoverLeaveEvent(QGraphicsSceneHoverEvent *event) override;

};

#endif // PIN_H
