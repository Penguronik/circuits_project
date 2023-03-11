#ifndef SCENE_H
#define SCENE_H

// HEADERS
#include "Frontend/graphicscomponents.h"
#include "graphicswire.h"
#include "graphicscircuitcomponent.h"

// QT
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QList>
#include <QBasicTimer>

class Scene : public QGraphicsScene
{
public:

    // Constructors
    explicit Scene(QObject *parent = nullptr);

    // Events
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;

    virtual void keyPressEvent(QKeyEvent *event) override;

    virtual void dragEnterEvent(QGraphicsSceneDragDropEvent *event) override;
    virtual void dragMoveEvent(QGraphicsSceneDragDropEvent *event) override;
    virtual void dropEvent(QGraphicsSceneDragDropEvent *event) override;

    virtual void timerEvent(QTimerEvent *event) override;

    // Getters
    QList<GraphicsCircuitComponent*> &componentList();

    // Public Functions
    void updateComponents();
    void addComponent(GraphicsCircuitComponent *component);
    void removeComponent(GraphicsCircuitComponent *component);
    GraphicsCircuitComponent *createComponent(QString componentType);
    void deleteItems();

private:
    GraphicsPinIn *currentPinIn_;
    GraphicsPinOut *currentPinOut_;
    GraphicsWire *currentWire_;
    QList<GraphicsCircuitComponent*> componentList_;
    GraphicsCircuitIn *GraphicsCircuitIn_;
    GraphicsCircuitOut *GraphicsCircuitOut_;
    QBasicTimer timer_;
};

#endif // SCENE_H
