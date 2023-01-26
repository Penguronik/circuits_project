//UTIL
#include "constants.h"

//HEADERS
#include <QMimeData>
#include "qevent.h"
#include "view.h"

View::View(QGraphicsScene * scene, QWidget * parent):
    QGraphicsView(scene, parent)
{
    setFixedSize(500, 500);
    setSceneRect(0, 0, 500, 500);
    fitInView(0, 0, 500, 500, Qt::KeepAspectRatio);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setAcceptDrops(true);
}
