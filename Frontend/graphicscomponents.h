#ifndef GRAPHICSCOMPONENTS_H
#define GRAPHICSCOMPONENTS_H

#include "Backend/components.cpp"
#include "graphicscircuitcomponent.h"

class GraphicsButtonPin : public QGraphicsEllipseItem
{
public:

    enum{Type = UserType + 5};
    int type() const override {return Type; }

    GraphicsButtonPin(qreal x, qreal y, qreal w, qreal h, QGraphicsItem *parent = nullptr);

    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
};

class GraphicsButtonComponent : public GraphicsCircuitComponent
{
public:

    // Qt Type
    enum{Type = UserType + 4};
    int type() const override { return Type; }

    GraphicsButtonComponent(ButtonComponent *circuitComponent, QGraphicsItem *parent = nullptr);

    virtual QRectF boundingRect() const override;
    virtual QPainterPath shape() const override;

    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;

    void setButtonState(bool state);

private:
    GraphicsButtonPin buttonPin_;
    ButtonComponent *buttonComponent_; //using this system to bypass problems with subclassing graphicscircuitcomponent, when you improve hierarchy by having a base circuitcomponent and another base for gates specifically then you can subclass this from the top and do it without this variable

};


#endif // GRAPHICSCOMPONENTS_H
