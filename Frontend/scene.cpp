#include "scene.h"
#include "Backend/circuitcomponent.h"
#include "Frontend/graphicscircuitcomponent.h"
#include "graphicspinbase.h"
#include <iostream>
#include "wire.h"

Scene::Scene(QObject *parent):
    QGraphicsScene{parent},
    currentPin{nullptr},
    currentWire{nullptr}
{

}

void Scene::mousePressEvent(QGraphicsSceneMouseEvent *event){

    // Get all items at clicked position and iterate through them.
    QList<QGraphicsItem*> candidateItems {items(event->scenePos())};
    QList<QGraphicsItem*>::const_iterator i{};
    for (i = candidateItems.constBegin(); i != candidateItems.constEnd(); ++i) {
        std::cout << (*i)->type() << std::endl;

        // Take the first item that is not a wire and cast it to currentPin if it is a Pin
        if (( (*i)->type() != Wire::Type )) {
            currentPin = qgraphicsitem_cast<GraphicsPinBase *>(*i);
            break;
        }
    }

    // If currentPin exists, create a wire that starts at the Pin's center
    if (currentPin) {

        QLineF lineShape{};
        if (currentPin->role() == GraphicsPinBase::State) {
            lineShape.setP1(currentPin->sceneBoundingRect().center());
            lineShape.setP2(event->scenePos());
        }
        else if (currentPin->role() == GraphicsPinBase::Out) {
            lineShape.setP1(event->scenePos());
            lineShape.setP2(currentPin->sceneBoundingRect().center());
        }
        currentWire = new Wire{lineShape};
        currentWire->setStyle(Wire::NotAttached);
        addItem(currentWire);
        currentPin->addWire(currentWire);
    }

    // If the event is not used, pass it to parent class
    else {
        QGraphicsScene::mousePressEvent(event);
    }
}

void Scene::mouseMoveEvent(QGraphicsSceneMouseEvent *event){
    if(currentPin){

        QLineF lineShape{currentWire->line()};
        if (currentPin->role() == GraphicsPinBase::State) {
            lineShape.setP2(event->scenePos());

        }
        else if (currentPin->role() == GraphicsPinBase::Out) {
            lineShape.setP1(event->scenePos());

        }
        currentWire->setLine(lineShape);

    }

    else {
        QGraphicsScene::mouseMoveEvent(event);
    }
}

void Scene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event){
    if(currentPin) {
        GraphicsPinBase *finalPin = nullptr;
        QList<QGraphicsItem*> candidateItems {items(event->scenePos())};
        QList<QGraphicsItem*>::const_iterator i{};
        for (i = candidateItems.constBegin(); i != candidateItems.constEnd(); ++i) {
            if ((*i)->type() != Wire::Type) {
                QGraphicsItem *item = *i;
                finalPin = qgraphicsitem_cast<GraphicsPinBase*>(item);
                break;
            }
        }

        if(( finalPin ) && ( finalPin->role() != currentPin->role() ) && ( finalPin != currentPin )) {

            QLineF lineShape{currentWire->line()};
            if (finalPin->role() == GraphicsPinBase::State) {
                lineShape.setP1(finalPin->sceneBoundingRect().center());
                GraphicsCircuitComponent::connect(finalPin, currentPin);
            }
            else if (finalPin->role() == GraphicsPinBase::Out) {
                lineShape.setP2(finalPin->sceneBoundingRect().center());
                GraphicsCircuitComponent::connect(currentPin, finalPin);
            }
            currentWire->setLine(lineShape);
            currentWire->setStyle(Wire::Attached);
            finalPin->addWire(currentWire);



        }

        else {
            currentPin->removeWire(currentWire);
            delete currentWire;
        }
        currentWire = nullptr;
        currentPin = nullptr;
    }

    else {
        QGraphicsScene::mouseReleaseEvent(event);
    }
}
