#ifndef WIRE_H
#define WIRE_H

// QT
#include <QGraphicsLineItem>

class Wire : public QGraphicsLineItem
{
public:

    // Enums
    //
    enum LineStyle {NotAttached = 0,
                    Attached    = 1
                   };

    // Constructors
    //
    Wire(const QLineF &line, QGraphicsItem *parent = nullptr);

    // Setters
    //
    void setStyle(LineStyle style);

};

#endif // WIRE_H
