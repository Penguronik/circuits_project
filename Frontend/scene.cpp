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
//#include <gpiod.h>

Scene::Scene(QObject *parent):
    QGraphicsScene{parent},
    currentPinIn_{nullptr},
    currentPinOut_{nullptr},
    currentWire_{nullptr},
    componentList_{},
    timer_{}
{
//    gpiod_chip *chip;
//    gpiod_line *lineOut1;
//    gpiod_line *lineIn1;
//    int i, val;

//    chip = gpiod_chip_open_by_name("gpiochip0");

//    lineOut1 = gpiod_chip_get_line(chip, 24);
//    lineIn1 = gpiod_chip_get_line(chip, 6);

//    gpiod_line_request_output(lineOut1, "circuits_project", 0);

//    gpiod_line_request_input(lineIn1, "circuits_project");

//    gpiod_line_get_value(lineIn1);

//    gpiod_line_set_value(lineOut1, 1);


    timer_.start(15, this);
    GraphicsCircuitIn *beginningGraphicsCircuitIn = new GraphicsCircuitIn{2};
    GraphicsCircuitOut *beginningGraphicsCircuitOut = new GraphicsCircuitOut{1};
    addItem(beginningGraphicsCircuitIn);
    addItem(beginningGraphicsCircuitOut);
    addComponent(beginningGraphicsCircuitIn);
    addComponent(beginningGraphicsCircuitOut);
}

void Scene::updateComponents() {
    bool circuitInput[2]{true, false};
    QList<GraphicsCircuitComponent*>::const_iterator i{};
    for (i = componentList().constBegin(); i != componentList().constEnd(); ++i) {
        GraphicsCircuitIn *circuitIn = qgraphicsitem_cast<GraphicsCircuitIn *>(*i);
        if (circuitIn) {
            circuitIn->run(circuitInput);
        }
    }

    for (i = componentList().constBegin(); i != componentList().constEnd(); ++i) {
        (*i)->updateStates();
    }
    for (i = componentList().constBegin(); i != componentList().constEnd(); ++i) {
        (*i)->run();
    }
    for (i = componentList().constBegin(); i != componentList().constEnd(); ++i) {
        (*i)->updateWires();
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
                // Cast to GraphicsPinIn if it is a pinIn, GraphicsPinOut if it is a pin out
                if ( (*i)->type() == GraphicsPinIn::Type ) {
                    currentPinIn_ = qgraphicsitem_cast<GraphicsPinIn *>(*i);
                } else if ( (*i)->type() == GraphicsPinOut::Type ) {
                    currentPinOut_ = qgraphicsitem_cast<GraphicsPinOut *>(*i);
                }
                break;
            }
        }

        // If currentPinIn exists, create a wire that starts at the pin's center
        if (currentPinIn_) {
            event->setAccepted(true); // so that rubber band isnt used
            clearSelection(); // clears selected items as the mouse click is accepted

            currentWire_ = new GraphicsWire{};

            currentWire_->setPinInPosition(currentPinIn_->sceneBoundingRect().center());
            currentWire_->setPinOutPosition(event->scenePos());

            currentWire_->setStyle(GraphicsWire::NotAttached);

            addItem(currentWire_);
        // Else if currentPinOut exists, create a wire that starts at the pin's center
        } else if (currentPinOut_) {
            event->setAccepted(true); // so that rubber band isnt used
            clearSelection(); // clears selected items as the mouse click is accepted

            currentWire_ = new GraphicsWire{};

            currentWire_->setPinInPosition(event->scenePos());
            currentWire_->setPinOutPosition(currentPinOut_->sceneBoundingRect().center());

            currentWire_->setStyle(GraphicsWire::NotAttached);

            addItem(currentWire_);
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
    if(currentPinIn_){

        currentWire_->setPinOutPosition(event->scenePos());

    } else if (currentPinOut_) {

        currentWire_->setPinInPosition(event->scenePos());

    }

    else {
        QGraphicsScene::mouseMoveEvent(event);
    }
}

void Scene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event){
    if(currentPinIn_) {
        QList<QGraphicsItem*> candidateItems {items(event->scenePos())};
        QList<QGraphicsItem*>::const_iterator i{};
        for (i = candidateItems.constBegin(); i != candidateItems.constEnd(); ++i) {

            if ((*i)->type() != GraphicsWire::Type) {
                currentPinOut_ = qgraphicsitem_cast<GraphicsPinOut *>(*i);
                break;
            }
        }

        if (currentPinOut_) {
            currentWire_->setPinOutPosition(currentPinOut_->sceneBoundingRect().center());

            currentWire_->connect(currentPinIn_, currentPinOut_); // if you want to allow for wire placements before full connection at some point then you'll have to move the addWire functions outside of the connect function
            currentWire_->setStyle(GraphicsWire::Attached);

        }

        else {
            delete currentWire_;
        }

        currentWire_ = nullptr;
        currentPinIn_ = nullptr;
        currentPinOut_ = nullptr;

    } else if (currentPinOut_) {
        QList<QGraphicsItem*> candidateItems {items(event->scenePos())};
        QList<QGraphicsItem*>::const_iterator i{};
        for (i = candidateItems.constBegin(); i != candidateItems.constEnd(); ++i) {

            if ((*i)->type() != GraphicsWire::Type) {
                currentPinIn_ = qgraphicsitem_cast<GraphicsPinIn *>(*i);
                break;
            }
        }

        if (currentPinIn_) {
            currentWire_->setPinInPosition(currentPinIn_->sceneBoundingRect().center());

            currentWire_->connect(currentPinIn_, currentPinOut_);
            currentWire_->setStyle(GraphicsWire::Attached);

        }

        else {
            delete currentWire_;
        }

        currentWire_ = nullptr;
        currentPinIn_ = nullptr;
        currentPinOut_ = nullptr;
    }

    else {
        QGraphicsScene::mouseReleaseEvent(event);
    }
}

void Scene::dragEnterEvent(QGraphicsSceneDragDropEvent *event) {
    if (event->mimeData()->hasFormat("application/json")) {
        event->acceptProposedAction();
        qDebug() << "Drag Enter";
    }
}

void Scene::dragMoveEvent(QGraphicsSceneDragDropEvent *event) {
    if (event->mimeData()->hasFormat("application/json")) {
        event->acceptProposedAction();
    }
}

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

void Scene::removeComponent(GraphicsCircuitComponent *component) {
    componentList_.removeAll(component);
}

GraphicsCircuitComponent *Scene::createComponent(QString componentType) {
    if (componentType == "NOT Gate") {
        return new GraphicsNOTGate{};
    } else if (componentType == "OR Gate") {
        return new GraphicsORGate{};
    } else if (componentType == "AND Gate") {
        return new GraphicsANDGate{};
    } else if (componentType == "Circuit In") {
        return new GraphicsCircuitIn{1};
    } else if (componentType == "Circuit Out") {
        return new GraphicsCircuitOut{1};
    } else if (componentType == "Button") {
        return new GraphicsButtonComponent{};
    } else if (componentType == "XOR Gate") {
        return new GraphicsXORGate{};
    }

    return nullptr;
}

QList<GraphicsCircuitComponent*> &Scene::componentList() {
    return componentList_;
}

void Scene::deleteItems()
{
    // remove wires first to prevent issues with wires trying to be deleted after a component already deleted the wire
    QList<QGraphicsItem *> candidateItems = selectedItems();
    QList<QGraphicsItem*>::const_iterator i{};
    for (i = candidateItems.constBegin(); i != candidateItems.constEnd(); ++i) {
        if ((*i)->type() == GraphicsWire::Type) {
            removeItem(*i);
            delete *i;
        }
    }

    candidateItems = selectedItems(); // get the new list without the wires
    for (i = candidateItems.constBegin(); i != candidateItems.constEnd(); ++i) {
        if ((*i)->type() > GraphicsCircuitComponent::Type) { // only the children of GraphicsCircuitComponent have a type greater than it
            GraphicsCircuitComponent *component = static_cast<GraphicsCircuitComponent *>(*i);
            removeComponent(component);
        }
        removeItem(*i);
        delete *i;
    }
}
