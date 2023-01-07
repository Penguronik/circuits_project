#include "scene.h"
#include "graphicspin.h"
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
            currentPin = qgraphicsitem_cast<GraphicsPin *>(*i);
            break;
        }
    }

    // If currentPin exists, create a wire that starts at the Pin's center
    if (currentPin) {

        QLineF lineShape{};
        if (currentPin->role() == GraphicsPin::State) {
            lineShape.setP1(currentPin->sceneBoundingRect().center());
            lineShape.setP2(event->scenePos());
        }
        else if (currentPin->role() == GraphicsPin::Out) {
            lineShape.setP1(event->scenePos());
            lineShape.setP2(currentPin->sceneBoundingRect().center());
        }
        currentWire = new Wire{lineShape};
        currentWire->setStyle(Wire::NotAttached);
        addItem(currentWire);
        currentPin->wireList_.append(currentWire);
    }

    // If the event is not used, pass it to parent class
    else {
        QGraphicsScene::mousePressEvent(event);
    }
}

void Scene::mouseMoveEvent(QGraphicsSceneMouseEvent *event){
    if(currentPin){

        QLineF lineShape{currentWire->line()};
        if (currentPin->role() == GraphicsPin::State) {
            lineShape.setP2(event->scenePos());

        }
        else if (currentPin->role() == GraphicsPin::Out) {
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
        GraphicsPin *finalPin = nullptr;
        QList<QGraphicsItem*> candidateItems {items(event->scenePos())};
        QList<QGraphicsItem*>::const_iterator i{};
        for (i = candidateItems.constBegin(); i != candidateItems.constEnd(); ++i) {
            if ((*i)->type() != Wire::Type) {
                QGraphicsItem *item = *i;
                finalPin = qgraphicsitem_cast<GraphicsPin*>(item);
                break;
            }
        }

        if(( finalPin ) && ( finalPin->role() != currentPin->role() ) && ( finalPin != currentPin )) {

            QLineF lineShape{currentWire->line()};
            if (finalPin->role() == GraphicsPin::State) {
                lineShape.setP1(finalPin->sceneBoundingRect().center());
            }
            else if (finalPin->role() == GraphicsPin::Out) {
                lineShape.setP2(finalPin->sceneBoundingRect().center());
            }
            currentWire->setLine(lineShape);
            currentWire->setStyle(Wire::Attached);
            finalPin->wireList_.append(currentWire);

        }

        else {
            currentPin->wireList_.removeOne(currentWire);
            delete currentWire;
        }
        currentWire = nullptr;
        currentPin = nullptr;
    }

    else {
        QGraphicsScene::mouseReleaseEvent(event);
    }
}
