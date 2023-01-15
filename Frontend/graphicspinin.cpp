#include "graphicspinin.h"

GraphicsPinIn::GraphicsPinIn(qreal x, qreal y, qreal width, qreal height, PinIn *pin, int index, QGraphicsItem *parent):
    GraphicsPinBase{x, y, width, height, GraphicsPinBase::State, pin, index, parent}
{

}
