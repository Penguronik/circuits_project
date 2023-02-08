//UTIL
#include "constants.h"
#include <iostream> //remove all iostreams at the end

//HEADERS
#include "graphicscircuitcomponent.h"
#include "graphicspinin.h"
#include "graphicspinout.h"
#include "body.h"
#include "qgraphicssceneevent.h"

//QT
#include <QGraphicsView>
#include <QKeyEvent>

GraphicsCircuitComponent::GraphicsCircuitComponent(CircuitComponent *circuitComponent, QGraphicsItem *parent):
    QGraphicsItem{parent},
    body_{new Body{0, 0, 50, 30, this}}, //A RENAME IS DEFINITELY NECESSARY VERY SOON
    inPinList_{}, //consider making them arrays instead of lists
    outPinList_{},
    circuitComponent_{circuitComponent}
{
    generateInPins();
    generateOutPins();
    setFlag(QGraphicsItem::ItemIsMovable);
}

GraphicsCircuitComponent::~GraphicsCircuitComponent() {
    delete body_;
    body_ = nullptr;
    qDeleteAll(inPinList_);
    inPinList_.clear();
    qDeleteAll(outPinList_);
    outPinList_.clear();
    delete circuitComponent_;
    circuitComponent_ = nullptr;
}

QRectF GraphicsCircuitComponent::boundingRect() const{
    return body_->boundingRect();
}

void GraphicsCircuitComponent::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
    //Empty paint, container item
}

QPainterPath GraphicsCircuitComponent::shape() const {
    return body_->shape();
}

void GraphicsCircuitComponent::generateInPins() {
    qreal interval {body_->boundingRect().height()/circuitComponent_->inSize()};
    QPointF topLeft {body_->boundingRect().topLeft()};
    topLeft.setY(topLeft.y() + interval/2 - constant::PIN_DIAMETER/2);
    topLeft.setX(topLeft.x() - constant::PIN_DIAMETER/2);
    for (int i {0}; i < circuitComponent_->inSize(); i++) {
        inPinList_.append(new GraphicsPinIn{topLeft.x(), topLeft.y() + interval*i, constant::PIN_DIAMETER, constant::PIN_DIAMETER, circuitComponent_->pinInArray() + i, i, this});
    }
}

void GraphicsCircuitComponent::generateOutPins() {
    qreal interval {body_->boundingRect().height()/circuitComponent_->outSize()};
    QPointF topRight {body_->boundingRect().topRight()};
    topRight.setY(topRight.y() + interval/2 - constant::PIN_DIAMETER/2);
    topRight.setX(topRight.x() - constant::PIN_DIAMETER/2);
    for (int i {0}; i < circuitComponent_->outSize(); i++) {
        outPinList_.append(new GraphicsPinOut{topRight.x(), topRight.y() + interval*i, constant::PIN_DIAMETER, constant::PIN_DIAMETER, circuitComponent_->pinOutArray() + i, i, this});
    }
}

void GraphicsCircuitComponent::updateStates() {
    circuitComponent_->updateStates();
}

void GraphicsCircuitComponent::updateWires() {
    circuitComponent_->updateWires();
}

void GraphicsCircuitComponent::run() {
    circuitComponent_->run();
}

void GraphicsCircuitComponent::updatePinColors() {
    QList<GraphicsPinIn*>::iterator currentPinIn{};
    for (currentPinIn = inPinList_.begin(); currentPinIn != inPinList_.end(); ++currentPinIn) {
        (*currentPinIn)->updatePinColor();
    }
    QList<GraphicsPinOut*>::iterator currentPinOut{};
    for (currentPinOut = outPinList_.begin(); currentPinOut != outPinList_.end(); ++currentPinOut) {
        (*currentPinOut)->updatePinColor();
    }
}

void GraphicsCircuitComponent::mouseReleaseEvent(QGraphicsSceneMouseEvent *event) {
    scene()
}
