#ifndef GRAPHICSCIRCUITIO_H
#define GRAPHICSCIRCUITIO_H

#include "graphicsgates.h"
#include "Frontend/graphicspinbase.h"
#include <QGraphicsItem>

class GraphicsCircuitIO : public QGraphicsItem
{
public:

    // Qt Type
    enum{Type = UserType + 9};
    int type() const override { return Type; }

    // Constructors
    explicit GraphicsCircuitIO(CircuitIO *circuitIO, QGraphicsItem *parent = nullptr);
    explicit GraphicsCircuitIO(int inSize, int outSize, QGraphicsItem *parent = nullptr);

    // Destructor
    ~GraphicsCircuitIO();

    // Getters
    virtual QRectF boundingRect() const override;

    // Public Functions
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
    void generateInPins();
    void generateOutPins();
    void generatePins();
    void updateStates();
    void updateWires();
    void run(); // this exists for debugging purposes, eventually disable or make it work for the outside IO so its on a clock
    void run(bool input[]);
    void updatePinColors();

private:
    QList<GraphicsPinIn*> inPinList_;
    QList<GraphicsPinOut*> outPinList_;
    CircuitIO *circuitIO_;
};

#endif // GRAPHICSCIRCUITIO_H
