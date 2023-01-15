#ifndef GRAPHICSPINBASE_H
#define GRAPHICSPINBASE_H

// Headers
#include "Backend/pinbase.h"
#include "Backend/pinin.h"
#include "Backend/pinout.h"
#include "wire.h"

// QT
#include <QGraphicsEllipseItem>
#include <QRubberBand>

class GraphicsPinBase : public QGraphicsEllipseItem
{
public:

    // Enums
    enum{Type = UserType};
    enum Role {State = 0,
               Out   = 1};

    // Constructors
    explicit GraphicsPinBase(qreal x, qreal y, qreal width, qreal height, Role role, PinBase *pin, int index, QGraphicsItem *parent = nullptr);
    explicit GraphicsPinBase(const QRectF &rect, Role role, PinBase *pin, int index, QGraphicsItem *parent = nullptr);

    // Events
    virtual void hoverEnterEvent(QGraphicsSceneHoverEvent *event) override;
    virtual void hoverLeaveEvent(QGraphicsSceneHoverEvent *event) override;
    virtual QVariant itemChange(QGraphicsItem::GraphicsItemChange change, const QVariant &value) override;

    // Getters
    inline int type() const override { return Type; }
    Role role() const;

    // Setters
    void setRole(Role newRole);

    //Public Functions
    void addWire(Wire *wire);
    void removeWire(Wire *wire);

    int index() const;
    void setIndex(int index);

    PinBase *pin() const;
    void setPin(PinBase *pin);

private:
    Role role_;
    QList<Wire*> wireList_;
    int index_;
    PinBase *pin_;
};

#endif // GRAPHICSPINBASE_H
