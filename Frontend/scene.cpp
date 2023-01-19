#include "scene.h"
#include "graphicspinbase.h"
#include <iostream>
#include "graphicswire.h"
#include "graphicspinin.h"
#include "graphicspinout.h"

Scene::Scene(QObject *parent):
    QGraphicsScene{parent},
    tempPinIn{nullptr},
    tempPinOut{nullptr},
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
        if (( (*i)->type() != GraphicsWire::Type )) {
            // FIX COMMENTS THIS IS WRONG: Cast to GraphicsPinIn if it is a pinIn, GraphicsPinOut if it is a pin out, and nullptr otherwise
            if ( (*i)->type() == GraphicsPinIn::Type ) {
                tempPinIn = qgraphicsitem_cast<GraphicsPinIn *>(*i);
            } else if ( (*i)->type() == GraphicsPinOut::Type ) {
                tempPinOut = qgraphicsitem_cast<GraphicsPinOut *>(*i);
            }
            break;
        }
    }

    // If currentPin exists, create a wire that starts at the Pin's center
    if (tempPinIn) {

        currentWire = new GraphicsWire{};

        currentWire->setPinInPosition(tempPinIn->sceneBoundingRect().center());
        currentWire->setPinOutPosition(event->scenePos());

        currentWire->setStyle(GraphicsWire::NotAttached);

        addItem(currentWire);
    } else if (tempPinOut) {

        currentWire = new GraphicsWire{};

        currentWire->setPinInPosition(event->scenePos());
        currentWire->setPinOutPosition(tempPinOut->sceneBoundingRect().center());

        currentWire->setStyle(GraphicsWire::NotAttached);

        addItem(currentWire);
    }

    // If the event is not used, pass it to parent class
    else {
        QGraphicsScene::mousePressEvent(event);
    }
}

void Scene::mouseMoveEvent(QGraphicsSceneMouseEvent *event){
    if(tempPinIn){

        currentWire->setPinOutPosition(event->scenePos());

    } else if (tempPinOut) {

        currentWire->setPinInPosition(event->scenePos());

    }

    else {
        QGraphicsScene::mouseMoveEvent(event);
    }
}

void Scene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event){
    if(tempPinIn) {
        QList<QGraphicsItem*> candidateItems {items(event->scenePos())};
        QList<QGraphicsItem*>::const_iterator i{};
        for (i = candidateItems.constBegin(); i != candidateItems.constEnd(); ++i) {

            if ((*i)->type() != GraphicsWire::Type) {
                tempPinOut = qgraphicsitem_cast<GraphicsPinOut *>(*i);
                break;
            }
        }

        if (tempPinOut) {
            currentWire->setPinOutPosition(tempPinOut->sceneBoundingRect().center());

            currentWire->connect(tempPinIn, tempPinOut); // if you want to allow for wire placements before full connection at some point then you'll have to move the addWire functions outside of the connect function
            currentWire->setStyle(GraphicsWire::Attached);

        }

        else {
            tempPinIn->removeWire(currentWire);
            delete currentWire;
        }

        currentWire = nullptr;
        tempPinIn = nullptr;
        tempPinOut = nullptr;

    } else if (tempPinOut) {
        QList<QGraphicsItem*> candidateItems {items(event->scenePos())};
        QList<QGraphicsItem*>::const_iterator i{};
        for (i = candidateItems.constBegin(); i != candidateItems.constEnd(); ++i) {

            if ((*i)->type() != GraphicsWire::Type) {
                tempPinIn = qgraphicsitem_cast<GraphicsPinIn *>(*i);
                break;
            }
        }

        if (tempPinIn) {
            currentWire->setPinInPosition(tempPinIn->sceneBoundingRect().center());

            currentWire->connect(tempPinIn, tempPinOut);
            currentWire->setStyle(GraphicsWire::Attached);

        }

        else {
            tempPinOut->removeWire(currentWire);
            delete currentWire;
        }

        currentWire = nullptr;
        tempPinIn = nullptr;
        tempPinOut = nullptr;
    }

    else {
        QGraphicsScene::mouseReleaseEvent(event);
    }
}
