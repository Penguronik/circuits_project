//UTIL
#include "constants.h"

//HEADERS
#include "view.h"

View::View(QGraphicsScene * scene, QWidget * parent):
    QGraphicsView(scene, parent)
{
    setFixedSize(constant::WIDTH, constant::HEIGHT);
    setSceneRect(0, 0, constant::WIDTH, constant::HEIGHT);
    fitInView(0, 0, constant::WIDTH, constant::HEIGHT, Qt::KeepAspectRatio);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
}
