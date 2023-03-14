//UTIL
#include "constants.h"
#include <iostream> //remove all iostreams at the end

//HEADERS
#include "graphicscircuitcomponent.h"
#include "graphicspinin.h"
#include "graphicspinout.h"
#include "qgraphicssceneevent.h"
#include "qstyle.h"
#include "qstyleoption.h"

//QT
#include <QGraphicsView>
#include <QKeyEvent>

// All subclasses of GraphicsCircuitComponent have to implement generatePins() and generate their own pins and set the value of painterPath_

GraphicsCircuitComponent::GraphicsCircuitComponent(CircuitComponent *circuitComponent, QGraphicsItem *parent):
    QGraphicsItem{parent},
    pinInList_{}, //consider making them arrays instead of lists
    pinOutList_{},
    circuitComponent_{circuitComponent},
    painterPath_{}
{
    setFlag(QGraphicsItem::ItemIsMovable);
    setFlag(QGraphicsItem::ItemIsSelectable);
}

GraphicsCircuitComponent::~GraphicsCircuitComponent() {
    qDeleteAll(pinInList_);
    pinInList_.clear();
    qDeleteAll(pinOutList_);
    pinOutList_.clear();
    delete circuitComponent_;
    circuitComponent_ = nullptr;
}

QRectF GraphicsCircuitComponent::boundingRect() const {
    // Add 2 on each side of the rectangle for buffer for default pen size of 4 (+4 on width with -2 top x means +2 on bottom x)
    return QRectF{-2, -2, painterPath_.boundingRect().width() + 4, painterPath_.boundingRect().height() + 4};
}

QPainterPath GraphicsCircuitComponent::shape() const {
    return painterPath_;
}

// Default implementation of paint for most gates/components
void GraphicsCircuitComponent::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    painter->setBrush(Qt::gray);
    if (option->state.testFlag(QStyle::State_Selected)) {
        painter->setPen(QPen{Qt::black, 3, Qt::DashLine});
    } else {
        painter->setPen(QPen{Qt::black, 3});
    }
    painter->drawPath(painterPath_);
}

void GraphicsCircuitComponent::addPinInAtCenterPoint(qreal x, qreal y, int pinIndex) {
    pinInList_.append(new GraphicsPinIn{x - constant::PIN_DIAMETER/2, y - constant::PIN_DIAMETER/2, constant::PIN_DIAMETER, constant::PIN_DIAMETER, circuitComponent_->pinInArray() + pinIndex, this});
}

void GraphicsCircuitComponent::addPinOutAtCenterPoint(qreal x, qreal y, int pinIndex) {
    pinOutList_.append(new GraphicsPinOut{x - constant::PIN_DIAMETER/2, y - constant::PIN_DIAMETER/2, constant::PIN_DIAMETER, constant::PIN_DIAMETER, circuitComponent_->pinOutArray() + pinIndex, this});
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
    for (currentPinIn = pinInList_.begin(); currentPinIn != pinInList_.end(); ++currentPinIn) {
        (*currentPinIn)->updatePinColor();
    }
    QList<GraphicsPinOut*>::iterator currentPinOut{};
    for (currentPinOut = pinOutList_.begin(); currentPinOut != pinOutList_.end(); ++currentPinOut) {
        (*currentPinOut)->updatePinColor();
    }
}
