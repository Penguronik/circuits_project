#ifndef SCENE_H
#define SCENE_H

// HEADERS
#include "graphicswire.h"

// QT
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QList>

class Scene : public QGraphicsScene
{
public:

    // Constructors
    explicit Scene(QObject *parent = nullptr);

    // Events
    //
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;

private:
    // For processes where keeping track of the pins for a short period of time is necessary
    GraphicsPinIn *tempPinIn;
    GraphicsPinOut *tempPinOut;
    GraphicsWire *currentWire;
};

#endif // SCENE_H
