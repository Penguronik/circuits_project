#ifndef PIN_H
#define PIN_H

// Headers
#include "wire.h"

// QT
#include <QGraphicsEllipseItem>
#include <QRubberBand>

class Pin : public QGraphicsEllipseItem
{
public:

    // Enums
    //
    enum{Type = UserType};
    enum Role {State = 0,
               Out   = 1};

    // Constructors
    //
    explicit Pin(qreal x, qreal y, qreal width, qreal height, Role role, QGraphicsItem *parent = nullptr);
    explicit Pin(const QRectF &rect, Role role, QGraphicsItem *parent = nullptr);
//    explicit Pin(QGraphicsItem *parent = nullptr);

    // Events
    //
    virtual void hoverEnterEvent(QGraphicsSceneHoverEvent *event) override;
    virtual void hoverLeaveEvent(QGraphicsSceneHoverEvent *event) override;
    virtual QVariant itemChange(QGraphicsItem::GraphicsItemChange change, const QVariant &value) override;

    // Getters
    //
    inline int type() const override { return Type; }
    Role role() const;


    // Setters
    //
    void setRole(Role newRole);

    // Public Variables
    //
    QList<Wire*> wireList_;

    //Temp
    //
    int id_;
    inline static int currentId_ = 0;

private:
    Role role_;

};

#endif // PIN_H
