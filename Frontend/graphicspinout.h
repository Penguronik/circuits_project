#ifndef GRAPHICSPINOUT_H
#define GRAPHICSPINOUT_H

#include "Backend/pinout.h"
#include "graphicspinbase.h"

class GraphicsPinOut : public GraphicsPinBase
{
public:
    GraphicsPinOut(qreal x, qreal y, qreal width, qreal height, PinOut *pin, int index, QGraphicsItem *parent = nullptr);

private:

};

#endif // GRAPHICSPINOUT_H
