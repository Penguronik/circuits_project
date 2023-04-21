#include "graphicscomponents.h"
#include "qstyleoption.h"

GraphicsButtonComponent::GraphicsButtonComponent(ButtonComponent *circuitComponent, QGraphicsItem *parent):
    GraphicsCircuitComponent(circuitComponent, parent),
    buttonCircle_{12.5, 12.5, 25, 25, this}
{
    int sideLength = 50; // drawn as a rounded square
    painterPath_.addRoundedRect(0, 0, sideLength, sideLength, sideLength/10, sideLength/10);

    generatePins();
}

void GraphicsButtonComponent::generatePins() {
    QRectF rect = painterPath_.boundingRect();

    // pin-outs
    addPinOutAtCenterPoint(rect.width(), rect.height()/2, 0);
}

void GraphicsButtonComponent::setButtonState(bool state) {
    static_cast<ButtonComponent *>(circuitComponent_)->setState(state);
}

GraphicsButtonCircle::GraphicsButtonCircle(qreal x, qreal y, qreal w, qreal h, QGraphicsItem *parent):
    QGraphicsEllipseItem(0, 0, w, h, parent)
{
    setPos(x, y);
    setBrush(QBrush{Qt::red});
}

void GraphicsButtonCircle::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    GraphicsButtonComponent *parentButton = qgraphicsitem_cast<GraphicsButtonComponent *>(parentItem());
    parentButton->setButtonState(true);
}

void GraphicsButtonCircle::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    GraphicsButtonComponent *parentButton = qgraphicsitem_cast<GraphicsButtonComponent *>(parentItem());
    parentButton->setButtonState(false);
}

GraphicsCircuitIn::GraphicsCircuitIn(CircuitIn *circuitComponent, QGraphicsItem *parent):
    GraphicsCircuitComponent(circuitComponent, parent)
{
    int height = 70; // drawn as a rounded rect
    int width = 30;
    painterPath_.addRoundedRect(0, 0, width, height, 5, 5);

    generatePins();
}

GraphicsCircuitIn::GraphicsCircuitIn(gpiod_chip *chip, int inSize, QGraphicsItem *parent):
    GraphicsCircuitIn(new CircuitIn{chip, inSize}, parent)
{

}

void GraphicsCircuitIn::generatePins() {
    QRectF rect = painterPath_.boundingRect();

    // pin-outs (pin-outs used for CircuitIn component as the data is coming "in" from the outside)
    qreal interval {rect.height()/(circuitComponent_->outSize() + 1)};
    qDebug() << circuitComponent_->outSize();
    qDebug() << circuitComponent_->inSize();
    for (int i = 0; i < circuitComponent_->outSize(); i++) {
        addPinOutAtCenterPoint(rect.width(), interval*(i + 1), i);
    }
}

void GraphicsCircuitIn::run(bool input[]) {
    static_cast<CircuitIn *> (circuitComponent_)->run(input);
}

GraphicsCircuitOut::GraphicsCircuitOut(CircuitOut *circuitComponent, QGraphicsItem *parent):
    GraphicsCircuitComponent(circuitComponent, parent)
{
    int height = 70; // drawn as a rounded rect
    int width = 30;
    painterPath_.addRoundedRect(0, 0, width, height, 5, 5);

    generatePins();
}

GraphicsCircuitOut::GraphicsCircuitOut(gpiod_chip *chip, int outSize, QGraphicsItem *parent):
    GraphicsCircuitOut(new CircuitOut{chip, outSize}, parent)
{

}

void GraphicsCircuitOut::generatePins() {
    QRectF rect = painterPath_.boundingRect();

    // pin-ins (pin-ins used for CircuitOut component as the data is going "out" to the outside)
    qreal interval {rect.height()/(circuitComponent_->inSize() + 1)};
    qDebug() << circuitComponent_->outSize();
    qDebug() << circuitComponent_->inSize();
    for (int i = 0; i < circuitComponent_->inSize(); i++) {
        addPinInAtCenterPoint(0, interval*(i + 1), i);
    }
}

