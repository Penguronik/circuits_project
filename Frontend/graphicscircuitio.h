#ifndef GRAPHICSCIRCUITIO_H
#define GRAPHICSCIRCUITIO_H

#include "Backend/gates.h"
#include "Frontend/graphicspinbase.h"
#include <QGraphicsItem>

class GraphicsCircuitIO : public QGraphicsItem
{
public:

    // Qt Type
    enum{Type = UserType + 9};
    int type() const override { return Type; }

    explicit GraphicsCircuitIO(CircuitIO *circuitIO, QGraphicsItem *parent = nullptr);

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
