#include "body.h"
#include "qpainter.h"

Body::Body(qreal x, qreal y, qreal width, qreal height, QGraphicsItem *parent):
    QGraphicsRectItem{0, 0, width, height, parent} // Original rectangle is set to 0, 0 in order to use pos() instead of boundingrect() to follow position
{
    setPos(x, y);
}

//QRectF Body::boundingRect() const{
//    return QRectF{0, 0, 100, 200};
//}

void Body::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
//    QPainterPath path{};
//    path.addRoundedRect(rect().x(), rect().y(), rect().width()-1, rect().height()-1, 5, 5);
//    painter->setPen(QPen{Qt::black, 2});
//    painter->setBrush(Qt::gray);
//    painter->drawPath(path);
}

QPainterPath Body::shape() const {
    QPainterPath path{};
    path.addRoundedRect(rect(), 5, 5);
    return path;
}
