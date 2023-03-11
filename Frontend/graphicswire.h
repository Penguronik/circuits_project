#ifndef GRAPHICSWIRE_H
#define GRAPHICSWIRE_H

#include "Backend/wire.h"
#include "Frontend/graphicscircuitcomponent.h"

// QT
#include <QGraphicsLineItem>

class GraphicsPinIn;
class GraphicsPinOut;

class GraphicsWire : public QGraphicsLineItem
{
public:

    // Qt Type
    enum{Type = 0b10000000000000011};
    int type() const override { return Type; }

    // Enums
    enum LineStyle {NotAttached = 0,
                    Attached    = 1
                   };

    // Constructors
    GraphicsWire(Wire *wire = new Wire{}, QGraphicsItem *parent = nullptr);

    // Destructor
    ~GraphicsWire();

    // Setters
    void setStyle(LineStyle style);

    void connect(GraphicsPinIn *graphicsPinIn, GraphicsPinOut *graphicsPinOut);

    void connect(GraphicsPinOut *graphicsPinOut, GraphicsPinIn *graphicsPinIn);

    void setPinInPosition(QPointF position);

    void setPinOutPosition(QPointF position);

    // Getters
    GraphicsPinIn *pinIn() const;
    GraphicsPinOut *pinOut() const;
    Wire *wire() const;

private:
    Wire *wire_;
    GraphicsPinIn *graphicsPinIn_;
    GraphicsPinOut *graphicsPinOut_;
    void disconnect(); // should only be called from the destructor
};

#endif // GRAPHICSWIRE_H
