#ifndef GRAPHICSPINBASE_H
#define GRAPHICSPINBASE_H

// Headers
#include "graphicswire.h"

// QT
#include <QGraphicsEllipseItem>
#include <QRubberBand>

class GraphicsPinBase : public QGraphicsEllipseItem
{
public:

    // Qt Type
    enum{Type = 0b10000000000000000};
    virtual int type() const override { return Type; }

    // Constructors
    explicit GraphicsPinBase(qreal x, qreal y, qreal width, qreal height, QGraphicsItem *parent = nullptr);
    explicit GraphicsPinBase(const QRectF &rect, QGraphicsItem *parent = nullptr);

    // Destructors
    virtual ~GraphicsPinBase();

    // Getters
    virtual bool state() const = 0;

    // Public Functions
    void addWire(GraphicsWire *wire);
    void removeWire(GraphicsWire *wire);
    void updatePinColor();

protected:
    QList<GraphicsWire*> wireList_;

};

#endif // GRAPHICSPINBASE_H
