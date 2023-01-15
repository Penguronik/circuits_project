#ifndef GRAPHICSPININ_H
#define GRAPHICSPININ_H

#include "Backend/pinin.h"
#include "graphicspinbase.h"

class GraphicsPinIn : public GraphicsPinBase
{
public:
    GraphicsPinIn(qreal x, qreal y, qreal width, qreal height, PinIn *pin, int index, QGraphicsItem *parent = nullptr);


private:

};

#endif // GRAPHICSPININ_H
