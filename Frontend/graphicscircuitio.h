#ifndef GRAPHICSCIRCUITIO_H
#define GRAPHICSCIRCUITIO_H

#include "Backend/gates.h"
#include "Frontend/graphicspinbase.h"
#include <QGraphicsItem>

class GraphicsCircuitIO : public QGraphicsItem
{
public:

    enum{Type = UserType + 5}; // give type values to all of them

    explicit GraphicsCircuitIO(CircuitIO *circuitIO, QGraphicsItem *parent = nullptr);
    inline int type() const override { return Type; } // remember to add this when giving type to all

    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
    virtual QRectF boundingRect() const override;


    void generateInPins();
    void generateOutPins();
    void generatePins();

private:
    QList<GraphicsPinBase*> *inPinList_;
    QList<GraphicsPinBase*> *outPinList_;
    CircuitComponent *circuitIO_;
};

#endif // GRAPHICSCIRCUITIO_H
