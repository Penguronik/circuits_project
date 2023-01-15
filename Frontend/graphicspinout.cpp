#include "graphicspinout.h"

GraphicsPinOut::GraphicsPinOut(qreal x, qreal y, qreal width, qreal height, PinOut *pin, int index, QGraphicsItem *parent):
    GraphicsPinBase{x, y, width, height, GraphicsPinBase::Out, pin, index, parent}
{

}
