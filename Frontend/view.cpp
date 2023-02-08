//UTIL
#include "constants.h"

//HEADERS
#include <QMimeData>
#include "qevent.h"
#include <QGraphicsSceneEvent>
#include "view.h"


View::View(QGraphicsScene * scene, QWidget * parent):
    QGraphicsView(scene, parent)
{
//    setFixedSize(500, 500);
    setSceneRect(0, 0, 500, 500);
//    fitInView(0, 0, 500, 500, Qt::KeepAspectRatio);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setAcceptDrops(true);
    QPainter *painter{};
    painter->drawPixmap(QRect{0, 0, 50, 50}, QPixmap{"C:/Users/ronik/Programming/Qt/circuits_project/icons/Trash_Icon.png"});
    drawForeground(painter, QRectF{0, 0, 50, 50});
}

void View::resizeEvent(QResizeEvent *event) {
    fitInView(0, 0, 500, 500, Qt::KeepAspectRatio);
    QGraphicsView::resizeEvent(event);
}

//void View::mousePressEvent(QMouseEvent *event){
//    if (event->button() == Qt::RightButton) {
//        setDragMode(QGraphicsView::ScrollHandDrag);
//    } else {
//        QGraphicsView::mousePressEvent(event);
//    }
//}

//void View::mouseReleaseEvent(QMouseEvent *event) {
//    if (event->button() == Qt::RightButton) {
//        setDragMode(QGraphicsView::NoDrag);
//    } else {
//        QGraphicsView::mouseReleaseEvent(event);
//    }
//}

// Adapted from https://stackoverflow.com/a/41688654
void View::wheelEvent(QWheelEvent *event) {
    if (event->modifiers() & Qt::ControlModifier) {
        // zoom
        const ViewportAnchor anchor = transformationAnchor();
        setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
        int angle = event->angleDelta().y();
        qreal factor;
        if (angle > 0) {
            factor = 1.1;
        } else {
            factor = 0.9;
        }
        scale(factor, factor);
        setTransformationAnchor(anchor);
    } else {
        QGraphicsView::wheelEvent(event);
    }
}
