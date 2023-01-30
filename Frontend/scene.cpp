#include "scene.h"
#include "graphicspinbase.h"
#include <iostream>
#include "graphicswire.h"
#include "graphicspinin.h"
#include "graphicspinout.h"
#include "graphicscircuitcomponent.h"
#include "graphicsgates.h"
#include "graphicscomponents.h"
#include <QKeyEvent>
#include <QMimeData>
#include <QJsonDocument>
#include <QJsonObject>
#include <QIODevice>

Scene::Scene(QObject *parent):
    QGraphicsScene{parent},
    currentPinIn{nullptr},
    currentPinOut{nullptr},
    currentWire{nullptr},
    componentList_{},
    GraphicsIO_{new GraphicsCircuitIO{2, 1}},
    timer_{}
{
    timer_.start(15, this);
    addItem(GraphicsIO_);
    GraphicsIO_->generatePins();
}

void Scene::updateComponents() {
    bool circuitInput[2]{true, false};
    GraphicsIO_->run(circuitInput);
    QList<GraphicsCircuitComponent*>::const_iterator i{};
    for (i = componentList().constBegin(); i != componentList().constEnd(); ++i) {
        (*i)->updateStates();
        GraphicsIO_->updateStates();
    }
    for (i = componentList().constBegin(); i != componentList().constEnd(); ++i) {
        (*i)->run();
        GraphicsIO_->run();
    }
    for (i = componentList().constBegin(); i != componentList().constEnd(); ++i) {
        (*i)->updateWires();
        GraphicsIO_->updateWires();
    }
    for (i = componentList().constBegin(); i != componentList().constEnd(); ++i) {
        (*i)->updatePinColors();
    }
}

void Scene::timerEvent(QTimerEvent *event) {
    updateComponents();
}

void Scene::keyPressEvent(QKeyEvent *event) {
    if (event->key() == Qt::Key_Space) {
        updateComponents();
    } else {
        QGraphicsScene::keyPressEvent(event);
    }
}

void Scene::mousePressEvent(QGraphicsSceneMouseEvent *event){

    if (event->button() == Qt::LeftButton){
        // Get all items at clicked position and iterate through them.
        QList<QGraphicsItem*> candidateItems {items(event->scenePos())};
        QList<QGraphicsItem*>::const_iterator i{};
        for (i = candidateItems.constBegin(); i != candidateItems.constEnd(); ++i) {
    //        std::cout << (*i)->type() << std::endl;
            // Take the first item that is not a wire and cast it to currentPin if it is a Pin

            if (( (*i)->type() != GraphicsWire::Type )) {
                // FIX COMMENTS THIS IS WRONG: Cast to GraphicsPinIn if it is a pinIn, GraphicsPinOut if it is a pin out, and nullptr otherwise
                if ( (*i)->type() == GraphicsPinIn::Type ) {
                    currentPinIn = qgraphicsitem_cast<GraphicsPinIn *>(*i);
                } else if ( (*i)->type() == GraphicsPinOut::Type ) {
                    currentPinOut = qgraphicsitem_cast<GraphicsPinOut *>(*i);
                }
                break;
            }
        }

        // If currentPin exists, create a wire that starts at the Pin's center
        if (currentPinIn) {

            currentWire = new GraphicsWire{};

            currentWire->setPinInPosition(currentPinIn->sceneBoundingRect().center());
            currentWire->setPinOutPosition(event->scenePos());

            currentWire->setStyle(GraphicsWire::NotAttached);

            addItem(currentWire);
        } else if (currentPinOut) {

            currentWire = new GraphicsWire{};

            currentWire->setPinInPosition(event->scenePos());
            currentWire->setPinOutPosition(currentPinOut->sceneBoundingRect().center());

            currentWire->setStyle(GraphicsWire::NotAttached);

            addItem(currentWire);
        }

        // If the event is not used, pass it to parent class
        else {
            QGraphicsScene::mousePressEvent(event);
        }
    } else {
        QGraphicsScene::mousePressEvent(event);
    }
}

void Scene::mouseMoveEvent(QGraphicsSceneMouseEvent *event){
    if(currentPinIn){

        currentWire->setPinOutPosition(event->scenePos());

    } else if (currentPinOut) {

        currentWire->setPinInPosition(event->scenePos());

    }

    else {
        QGraphicsScene::mouseMoveEvent(event);
    }
}

void Scene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event){
    if(currentPinIn) {
        QList<QGraphicsItem*> candidateItems {items(event->scenePos())};
        QList<QGraphicsItem*>::const_iterator i{};
        for (i = candidateItems.constBegin(); i != candidateItems.constEnd(); ++i) {

            if ((*i)->type() != GraphicsWire::Type) {
                currentPinOut = qgraphicsitem_cast<GraphicsPinOut *>(*i);
                break;
            }
        }

        if (currentPinOut) {
            currentWire->setPinOutPosition(currentPinOut->sceneBoundingRect().center());

            currentWire->connect(currentPinIn, currentPinOut); // if you want to allow for wire placements before full connection at some point then you'll have to move the addWire functions outside of the connect function
            currentWire->setStyle(GraphicsWire::Attached);

        }

        else {
            currentPinIn->removeWire(currentWire);
            delete currentWire;
        }

        currentWire = nullptr;
        currentPinIn = nullptr;
        currentPinOut = nullptr;

    } else if (currentPinOut) {
        QList<QGraphicsItem*> candidateItems {items(event->scenePos())};
        QList<QGraphicsItem*>::const_iterator i{};
        for (i = candidateItems.constBegin(); i != candidateItems.constEnd(); ++i) {

            if ((*i)->type() != GraphicsWire::Type) {
                currentPinIn = qgraphicsitem_cast<GraphicsPinIn *>(*i);
                break;
            }
        }

        if (currentPinIn) {
            currentWire->setPinInPosition(currentPinIn->sceneBoundingRect().center());

            currentWire->connect(currentPinIn, currentPinOut);
            currentWire->setStyle(GraphicsWire::Attached);

        }

        else {
            currentPinOut->removeWire(currentWire);
            delete currentWire;
        }

        currentWire = nullptr;
        currentPinIn = nullptr;
        currentPinOut = nullptr;
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
