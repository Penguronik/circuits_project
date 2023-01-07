#ifndef SCENE_H
#define SCENE_H

// HEADERS
#include "wire.h"
#include "graphicspin.h"

// QT
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QList>

class Scene : public QGraphicsScene
{
public:

    // Constructors
    //
    explicit Scene(QObject *parent = nullptr);

    // Events
    //
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;

private:
    GraphicsPin *currentPin;
    Wire *currentWire;
};

#endif // SCENE_H
