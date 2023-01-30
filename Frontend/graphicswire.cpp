#include "graphicswire.h"
#include "Frontend/graphicspinin.h"
#include "Frontend/graphicspinout.h"
#include <QPen>

GraphicsWire::GraphicsWire(const QLineF &line, QGraphicsItem *parent):
    QGraphicsLineItem{line, parent},
    wire_{new Wire{}}
{

}

GraphicsWire::GraphicsWire(QGraphicsItem *parent):
    QGraphicsLineItem{parent},
    wire_{new Wire{}}
{

}

GraphicsWire::~GraphicsWire() {
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
