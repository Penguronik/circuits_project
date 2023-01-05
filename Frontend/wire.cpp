#include "wire.h"
#include <QPen>

Wire::Wire(const QLineF &line, QGraphicsItem *parent):
    QGraphicsLineItem{line, parent}
{

}

void Wire::setStyle(LineStyle style) {
        switch(style) {

        case 0:
            setPen(QPen{Qt::black, 2, Qt::DashLine});
            break;

        case 1:
            setPen(QPen{Qt::black, 2, Qt::SolidLine});
            break;

        }
    }
