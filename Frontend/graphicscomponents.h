#ifndef GRAPHICSCOMPONENTS_H
#define GRAPHICSCOMPONENTS_H

#include "Backend/components.cpp"
#include "graphicscircuitcomponent.h"

class GraphicsButtonCircle : public QGraphicsEllipseItem
{
public:

    enum{Type = 0b10000000000000100};
    int type() const override {return Type; }

    GraphicsButtonCircle(qreal x, qreal y, qreal w, qreal h, QGraphicsItem *parent = nullptr);

    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
};

class GraphicsButtonComponent : public GraphicsCircuitComponent
{
public:

    // Qt Type
    enum{Type = 0b11000000000000110};
    int type() const override { return Type; }

    GraphicsButtonComponent(ButtonComponent *circuitComponent = new ButtonComponent{}, QGraphicsItem *parent = nullptr);

    void setButtonState(bool state);

private:
    void generatePins();

    GraphicsButtonCircle buttonCircle_;

};

class GraphicsCircuitIn : public GraphicsCircuitComponent {
public:
    enum{Type = 0b11000000000000100};
    int type() const override {return Type; }

    GraphicsCircuitIn(CircuitIn *circuitComponent, QGraphicsItem *parent = nullptr);
    GraphicsCircuitIn(gpiod_chip *chip, int inSize, QGraphicsItem *parent = nullptr);

    void run(bool input[]);

private:
    void generatePins();

};

class GraphicsCircuitOut : public GraphicsCircuitComponent {
public:
    enum{Type = 0b11000000000000101};
    int type() const override {return Type; }

    GraphicsCircuitOut(CircuitOut *circuitComponent, QGraphicsItem *parent = nullptr);
    GraphicsCircuitOut(gpiod_chip *chip, int outSize, QGraphicsItem *parent = nullptr);

private:
    void generatePins();

};


#endif // GRAPHICSCOMPONENTS_H
