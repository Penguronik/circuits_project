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
    enum{Type = UserType + 10};
    virtual int type() const override { return Type; }

//    // Enums
//    enum Role {State = 0,
//               Out   = 1};

    // Constructors
    explicit GraphicsPinBase(qreal x, qreal y, qreal width, qreal height, int index, QGraphicsItem *parent = nullptr);
    explicit GraphicsPinBase(const QRectF &rect, int index, QGraphicsItem *parent = nullptr);

    // Events
    virtual void hoverEnterEvent(QGraphicsSceneHoverEvent *event) override;
    virtual void hoverLeaveEvent(QGraphicsSceneHoverEvent *event) override;

    // Getters
    virtual bool state() const = 0;
//    Role role() const;

    // Setters
//    virtual void setWirePinPosition() = 0;
//    virtual void setWireOtherPosition() = 0;

//    void setRole(Role newRole);

    // Public Functions
    void addWire(GraphicsWire *wire);
    void removeWire(GraphicsWire *wire);
    void updatePinColor();

//    int index() const;
//    void setIndex(int index);

//    void setPin(PinBase *pin);

protected:
    QList<GraphicsWire*> wireList_;
//    int index_;
};

#endif // GRAPHICSPINBASE_H
