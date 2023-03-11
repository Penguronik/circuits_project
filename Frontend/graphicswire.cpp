#include "graphicswire.h"
#include "Frontend/graphicspinin.h"
#include "Frontend/graphicspinout.h"
#include <QPen>

GraphicsWire::GraphicsWire(Wire *wire, QGraphicsItem *parent):
    QGraphicsLineItem{parent},
    wire_{wire},
    graphicsPinIn_{nullptr},
    graphicsPinOut_{nullptr}
{
    setFlags(QGraphicsItem::ItemIsSelectable);
}

GraphicsWire::~GraphicsWire() {
    disconnect(); // remove all references to the wire from the connected pins
    delete wire_;
    wire_ = nullptr;
}

void GraphicsWire::setStyle(LineStyle style) {
        switch(style) {

        case GraphicsWire::NotAttached:
            setPen(QPen{Qt::black, 2, Qt::DashLine});
            break;

        case GraphicsWire::Attached:
            setPen(QPen{Qt::black, 2, Qt::SolidLine});
            break;

        }
}

Wire *GraphicsWire::wire() const
{
    return wire_;
}

void GraphicsWire::connect(GraphicsPinIn *graphicsPinIn, GraphicsPinOut *graphicsPinOut) { //Make all objects pass by reference wherever possible if theyre not already a pointer
    wire_->connect(graphicsPinIn->pin(), graphicsPinOut->pin());
    graphicsPinIn->addWire(this);
    graphicsPinOut->addWire(this);
    graphicsPinIn_ = graphicsPinIn;
    graphicsPinOut_ = graphicsPinOut;
}

void GraphicsWire::connect(GraphicsPinOut *graphicsPinOut, GraphicsPinIn *graphicsPinIn) { //Make all objects pass by reference wherever possible if theyre not already a pointer
    connect(graphicsPinIn, graphicsPinOut);
}

void GraphicsWire::setPinInPosition(QPointF position) {
    QLineF lineShape{line()};
    lineShape.setP1(position);
    setLine(lineShape);
}

void GraphicsWire::setPinOutPosition(QPointF position) {
    QLineF lineShape{line()};
    lineShape.setP2(position);
    setLine(lineShape);
}

GraphicsPinIn *GraphicsWire::pinIn() const {
    return graphicsPinIn_;
}

GraphicsPinOut *GraphicsWire::pinOut() const {
    return graphicsPinOut_;
}

void GraphicsWire::disconnect() {
    if (graphicsPinIn_) graphicsPinIn_->removeWire(this); // Ensure graphicsPinIn_ is not nullptr
    if (graphicsPinOut_) graphicsPinOut_->removeWire(this);
    graphicsPinIn_ = nullptr;
    graphicsPinOut_ = nullptr;
}
