#include "body.h"
#include "qpainter.h"

Body::Body(qreal x, qreal y, qreal width, qreal height, QGraphicsItem *parent):
    QGraphicsRectItem{x, y, width, height, parent}
{

}

//QRectF Body::boundingRect() const{
//    return QRectF{0, 0, 100, 200};
//}

void Body::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
    QPainterPath path{};
    path.addRoundedRect(rect(), 5, 5);
    painter->setPen(QPen{Qt::black, 2});
    painter->drawPath(path);
    painter->fillPath(path, Qt::gray);
}

QPainterPath Body::shape() const {
    QPainterPath path{};
    path.addRoundedRect(rect(), 5, 5);
    return path;
}
