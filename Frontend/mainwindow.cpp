//UTIL
#include "Frontend/graphicsgates.h"
#include "Frontend/graphicscircuitio.h"
#include "constants.h"
#include <iostream>

//QT
#include <QGraphicsItem>
#include <QtGui/qevent.h>

//HEADERS
#include "Backend/gates.h"
#include "mainwindow.h"
#include "graphicspinbase.h"


MainWindow::MainWindow(QWidget *parent):
    QWidget{parent},
    scene_{new Scene{this}},
    view_{new View(scene_, this)},
    containerList_{new QList<GraphicsCircuitComponent*>},
    timer{}
{
    timer.start(15, this);
    scene_->setSceneRect(0, 0, constant::WIDTH, constant::HEIGHT);


    for (int i{}; i < 2; i++){
        ANDGate *circuit{new ANDGate{}};
        GraphicsANDGate *container{new GraphicsANDGate{circuit}};
        std::cout << container << "<- container address";
        containerList_->append(container);
        scene_->addItem(container);
    }

    ORGate *circuit{new ORGate{}};
    GraphicsORGate *container{new GraphicsORGate{circuit}};
    std::cout << container << "<- container address";
    containerList_->append(container);
    scene_->addItem(container);

    NOTGate *circuit2{new NOTGate{}};
    GraphicsNOTGate *container2{new GraphicsNOTGate{circuit2}};
    std::cout << container2 << "<- container address";
    containerList_->append(container2);
    scene_->addItem(container2);

    NOTGate *circuit3{new NOTGate{}};
    GraphicsNOTGate *container3{new GraphicsNOTGate{circuit3}};
    std::cout << container3 << "<- container address";
    containerList_->append(container3);
    scene_->addItem(container3);

    std::cout << "test";

    CircuitIO *IO{new CircuitIO{1,2}};
    GraphicsCircuitIO *GraphicsIO{new GraphicsCircuitIO{IO}};
    scene_->addItem(GraphicsIO);
    GraphicsIO->generatePins();
    IO_ = IO;
    GraphicsIO_ = GraphicsIO;


//    Circuit *circuit_1{new NOTGate{}};

//    ComponentContainer *test{new ComponentContainer{circuit_1}};

//    scene_->addItem(test);
//    test->setX(200);
//    test->setY(200);
//    test->setFlag(QGraphicsItem::ItemIsMovable);





//    QBrush greenBrush(Qt::green);
//    QBrush blueBrush(Qt::blue);
//    QPen outlinePen(Qt::black);
//    outlinePen.setWidth(2);

//    rectangle = scene->addRect(100, 0, 80, 100, outlinePen, blueBrush);

//    // addEllipse(x,y,w,h,pen,brush)
//    ellipse = scene->addEllipse(0, -100, 300, 60, outlinePen, greenBrush);

//    text = scene->addText("test", QFont("Arial", 20) );
//    // movable text
//    text->setFlag(QGraphicsItem::ItemIsMovable);
}

void MainWindow::resizeEvent(QResizeEvent *event) {
    QSize size{event->size()};
    view_->setFixedSize(size.width(), size.height());
    view_->setSceneRect(0, 0, size.width(), size.height());
    view_->fitInView(0, 0, size.width(), size.height(), Qt::KeepAspectRatio);
}

void MainWindow::keyPressEvent(QKeyEvent *event) {
    if (event->key() == Qt::Key_Space) {
        bool circuitInput[2]{true, false};
        IO_->run(circuitInput);
        QList<GraphicsCircuitComponent*>::const_iterator i{};
        for (i = containerList_->constBegin(); i != containerList_->constEnd(); ++i) {
            (*i)->updateStates();
            IO_->updateStates();
        }
        for (i = containerList_->constBegin(); i != containerList_->constEnd(); ++i) {
            (*i)->run();
        }
        for (i = containerList_->constBegin(); i != containerList_->constEnd(); ++i) {
            (*i)->updateWires();
            IO_->updateWires();
        }
        for (i = containerList_->constBegin(); i != containerList_->constEnd(); ++i) {
            (*i)->updatePinColors();
        }
        std::cout << "Output: " << IO_->pinInArray()->state() << std::endl;

    } else {
        QWidget::keyPressEvent(event);
    }
}

void MainWindow::timerEvent(QTimerEvent *event) {
    bool circuitInput[2]{true, false};
    IO_->run(circuitInput);
    QList<GraphicsCircuitComponent*>::const_iterator i{};
    for (i = containerList_->constBegin(); i != containerList_->constEnd(); ++i) {
        (*i)->updateStates();
        IO_->updateStates();
    }
    for (i = containerList_->constBegin(); i != containerList_->constEnd(); ++i) {
        (*i)->run();
    }
    for (i = containerList_->constBegin(); i != containerList_->constEnd(); ++i) {
        (*i)->updateWires();
        IO_->updateWires();
    }
    for (i = containerList_->constBegin(); i != containerList_->constEnd(); ++i) {
        (*i)->updatePinColors();
    }
    std::cout << "Output: " << IO_->pinInArray()->state() << std::endl;
}
