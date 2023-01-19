#ifndef GRAPHICSWIRE_H
#define GRAPHICSWIRE_H

#include "Backend/wire.h"

// QT
#include <QGraphicsLineItem>

class GraphicsPinIn;
class GraphicsPinOut;

class GraphicsWire : public QGraphicsLineItem
{
public:

    // Qt Type
    enum{Type = UserType + 20};
    int type() const override { return Type; }

    // Enums
    enum LineStyle {NotAttached = 0,
                    Attached    = 1
                   };

    // Constructors
    GraphicsWire(const QLineF &line, QGraphicsItem *parent = nullptr);
    GraphicsWire(QGraphicsItem *parent = nullptr);

    // Setters
    void setStyle(LineStyle style);

    Wire *wire() const;

    void connect(GraphicsPinIn *graphicsPinIn, GraphicsPinOut *graphicsPinOut);

    void connect(GraphicsPinOut *graphicsPinOut, GraphicsPinIn *graphicsPinIn);

    void setPinInPosition(QPointF position);

    void setPinOutPosition(QPointF position);

private:
    Wire *wire_;
};

#endif // GRAPHICSWIRE_H
