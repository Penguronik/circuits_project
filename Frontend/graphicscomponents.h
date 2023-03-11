#ifndef GRAPHICSCOMPONENTS_H
#define GRAPHICSCOMPONENTS_H

#include "Backend/components.cpp"
#include "graphicscircuitcomponent.h"

class GraphicsButtonPin : public QGraphicsEllipseItem
{
public:

    enum{Type = 0b10000000000000100};
    int type() const override {return Type; }

    GraphicsButtonPin(qreal x, qreal y, qreal w, qreal h, QGraphicsItem *parent = nullptr);

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

    virtual QRectF boundingRect() const override;
    virtual QPainterPath shape() const override;

    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;

    void setButtonState(bool state);

private:
    GraphicsButtonPin buttonPin_;

};

class GraphicsCircuitIn : public GraphicsCircuitComponent {
public:
    enum{Type = 0b11000000000000100};
    int type() const override {return Type; }

    GraphicsCircuitIn(CircuitIn *circuitComponent, QGraphicsItem *parent = nullptr);
    GraphicsCircuitIn(int inSize, QGraphicsItem *parent = nullptr);

    virtual QRectF boundingRect() const override;
    virtual QPainterPath shape() const override;

    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;

    void run(bool input[]);

};

class GraphicsCircuitOut : public GraphicsCircuitComponent {
public:
    enum{Type = 0b11000000000000101};
    int type() const override {return Type; }

    GraphicsCircuitOut(CircuitOut *circuitComponent, QGraphicsItem *parent = nullptr);
    GraphicsCircuitOut(int outSize, QGraphicsItem *parent = nullptr);

    virtual QRectF boundingRect() const override;
    virtual QPainterPath shape() const override;

    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
};


#endif // GRAPHICSCOMPONENTS_H
