#ifndef SCENE_H
#define SCENE_H

// HEADERS
#include "graphicswire.h"
#include "graphicscircuitcomponent.h"

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
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;

    virtual void dragEnterEvent(QGraphicsSceneDragDropEvent *event) override;
    virtual void dragMoveEvent(QGraphicsSceneDragDropEvent *event) override;
    virtual void dropEvent(QGraphicsSceneDragDropEvent *event) override;

    // Public Functions
    void addComponent(GraphicsCircuitComponent *component);
    GraphicsCircuitComponent *createComponent(QString componentType);

    QList<GraphicsCircuitComponent*> &componentList();

private:
    // For processes where keeping track of the pins for a short period of time is necessary
    GraphicsPinIn *tempPinIn;
    GraphicsPinOut *tempPinOut;
    GraphicsWire *currentWire;
    QList<GraphicsCircuitComponent*> componentList_;
};

#endif // SCENE_H
