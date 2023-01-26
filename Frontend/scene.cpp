#include "scene.h"
#include "graphicspinbase.h"
#include <iostream>
#include "graphicswire.h"
#include "graphicspinin.h"
#include "graphicspinout.h"
#include "graphicscircuitcomponent.h"
#include "graphicsgates.h"
#include "graphicscomponents.h"
#include <QMimeData>
#include <QJsonDocument>
#include <QJsonObject>
#include <QIODevice>

Scene::Scene(QObject *parent):
    QGraphicsScene{parent},
    tempPinIn{nullptr},
    tempPinOut{nullptr},
    currentWire{nullptr},
    componentList_{}
{

}

void Scene::mousePressEvent(QGraphicsSceneMouseEvent *event){

    // Get all items at clicked position and iterate through them.
    QList<QGraphicsItem*> candidateItems {items(event->scenePos())};
    QList<QGraphicsItem*>::const_iterator i{};
    for (i = candidateItems.constBegin(); i != candidateItems.constEnd(); ++i) {
//        std::cout << (*i)->type() << std::endl;

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

void Scene::dragEnterEvent(QGraphicsSceneDragDropEvent *event) {
    if (event->mimeData()->hasFormat("application/json")) {
        event->acceptProposedAction();
        qDebug() << event->proposedAction();
        event->setProposedAction(Qt::CopyAction);
        qDebug() << event->proposedAction();
//        event->acceptProposedAction();
        qDebug() << event->proposedAction();
        event->accept();
        qDebug() << "Drag Enter";
    }
}

void Scene::dragMoveEvent(QGraphicsSceneDragDropEvent *event) {
//    if (event->mimeData()->hasFormat("application/json")) {
//        qDebug() << event;
//        event->acceptProposedAction();
//    }
}

//void Scene ::dragLeaveEvent(QGraphicsSceneDragDropEvent *event) {


//}

void Scene::dropEvent(QGraphicsSceneDragDropEvent *event) {
    qDebug() << "Drag Drop";
    if (event->mimeData()->hasFormat("application/json")) {
        event->acceptProposedAction();

        QDataStream stream{event->mimeData()->data("application/json")};
        QByteArray encodedData {};

        stream >> encodedData;

        QJsonObject data{QJsonDocument::fromJson(encodedData).object()};

        if (data.value("Data").isString()) { // Base Gate/Component
            GraphicsCircuitComponent *component {createComponent(data.value("Data").toString())};
            qDebug() << "Scene Mime Accept: " << data.value("Data").toString();
            addItem(component);
            addComponent(component);

            component->setPos(event->scenePos() - component->boundingRect().center()); // Place the item's center right under the cursor

        } else if (data.value("Data").isObject()) {
            qDebug() << data.value("Data").toObject();
        }

    }

//    textBrowser->setPlainText(event->mimeData()->text());
//    mimeTypeCombo->clear();
//    mimeTypeCombo->addItems(event->mimeData()->formats());

//    event->acceptProposedAction();
}

void Scene::addComponent(GraphicsCircuitComponent *component) {
    componentList_.append(component);
}

GraphicsCircuitComponent *Scene::createComponent(QString componentType) {
    if (componentType == "NOT Gate") {
        return new GraphicsNOTGate{};
    } else if (componentType == "OR Gate") {
        return new GraphicsORGate{};
    } else if (componentType == "AND Gate") {
        return new GraphicsANDGate{};
    } else if (componentType == "Button") {
        return new GraphicsButtonComponent{};
    }

    return nullptr;
}

QList<GraphicsCircuitComponent*> &Scene::componentList() {
    return componentList_;
}
