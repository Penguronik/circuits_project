#include "graphicsgates.h"
#include "qstyleoption.h"


GraphicsANDGate::GraphicsANDGate(ANDGate *circuitComponent, QGraphicsItem *parent):
    GraphicsCircuitComponent(circuitComponent, parent)
{
    int rectWidth = 15;
    int height = 30; // also is circumference
    // draw top of rectangle
    painterPath_.lineTo(rectWidth, 0);
    // draw circular arc
    painterPath_.arcTo(rectWidth, 0, height, height, 90, -180);
    // draw bottom and left of rectangle
    painterPath_.lineTo(0, height);
    painterPath_.lineTo(0,0);

    generatePins();
}

void GraphicsANDGate::generatePins() {
    QRectF rect = painterPath_.boundingRect();

    // pin-ins
    qreal interval {rect.height()/4};
    addPinInAtCenterPoint(0, interval, 0);
    addPinInAtCenterPoint(0, interval*3, 1);

    // pin-outs
    addPinOutAtCenterPoint(rect.width(), rect.height()/2, 0);
}

GraphicsORGate::GraphicsORGate(ORGate *circuitComponent, QGraphicsItem *parent):
    GraphicsCircuitComponent(circuitComponent, parent)
{
    int radius = 35; // constructed from three arcs of the same radius
    QPainterPath arc1 {};
    QPainterPath arc2 {};
    //
    // Draw left arc   \
    //                 /
    //
    arc2.arcMoveTo(0, 0, 2*radius, 2*radius, 30);
    arc2.arcTo(0, 0, 2*radius, 2*radius, 30, -60);
    //
    // Draw top arc    \ \
    //                 /
    //
    arc1.arcMoveTo(1.25*radius, 0.5*radius, 2*radius, 2*radius, 30);
    arc1.arcTo(1.25*radius, 0.5*radius, 2*radius, 2*radius, 30, 60);
    //
    // Draw bottom arc \ \
    //                 / /
    //
    painterPath_.arcMoveTo(1.25*radius, -0.5*radius, 2*radius, 2*radius, -90);
    painterPath_.arcTo(1.25*radius, -0.5*radius, 2*radius, 2*radius, -90, 60);
    //                 __
    // Connect arcs    \ \
    // with lines      /_/
    //
    arc1.connectPath(arc2);
    painterPath_.connectPath(arc1);
    painterPath_.lineTo(2.25*radius, 1.5*radius);

    // Translate path such that (0, 0) is it's top left corner
    painterPath_.translate(-painterPath_.boundingRect().x(), -painterPath_.boundingRect().y());

    generatePins();
}

void GraphicsORGate::generatePins() {
    QRectF rect = painterPath_.boundingRect();

    // pin-ins
    qreal interval {rect.height()/4};
    addPinInAtCenterPoint(0, interval, 0);
    addPinInAtCenterPoint(0, interval*3, 1);

    // pin-outs
    addPinOutAtCenterPoint(rect.width(), rect.height()/2, 0);
}

GraphicsNOTGate::GraphicsNOTGate(NOTGate *circuitComponent, QGraphicsItem *parent):
    GraphicsCircuitComponent(circuitComponent, parent)
{
    int sideLength = 40; // drawn as an equalitarel triangle
    int radius = 5; // the "not" circle radius
    const double SQRT3_2 = 0.86602540378443864676; // sqrt(3)/2 stored as constant
    // Draw triangle
    painterPath_.lineTo(sideLength*SQRT3_2, sideLength/2);
    painterPath_.lineTo(0, sideLength);
    painterPath_.lineTo(0,0);
    // Draw "not" circle
    painterPath_.moveTo(sideLength*SQRT3_2, sideLength/2);
    painterPath_.addEllipse(sideLength*SQRT3_2, sideLength/2-radius, radius*2, radius*2);

    generatePins();
}

void GraphicsNOTGate::generatePins() {
    QRectF rect = painterPath_.boundingRect();

    // pin-ins
    addPinInAtCenterPoint(0, rect.height()/2, 0);

    // pin-outs
    addPinOutAtCenterPoint(rect.width() + 2.5, rect.height()/2, 0);
}

