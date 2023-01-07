//UTIL
#include "constants.h"
#include <iostream>

//QT
#include <QGraphicsItem>
#include <QtGui/qevent.h>

//HEADERS
#include "Backend/interface.h"
#include "Backend/gates.h"
#include "mainwindow.h"
#include "graphicspin.h"


MainWindow::MainWindow(QWidget *parent):
    QWidget{parent},
    scene_{new Scene{this}},
    view_{new View(scene_, this)},
    containerList_{new QList<ComponentContainer*>}
{
    scene_->setSceneRect(0, 0, constant::WIDTH, constant::HEIGHT);


//    Interface *interface{new Interface{}};

//    Component *component_1{new Component{interface->newComponent()}}; //Component may be already used by qt?


    for (int i{}; i < 3; i++){
        Circuit *circuit{new NOTGate{}};
        ComponentContainer *container{new ComponentContainer{circuit}};
        std::cout << container << "<- container address";
        containerList_->append(container);
        scene_->addItem(container);
    }

    Circuit *circuit{new ANDGate{}};
    ComponentContainer *container{new ComponentContainer{circuit}};
    std::cout << container << "<- container address";
    containerList_->append(container);
    scene_->addItem(container);

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

//    text = scene->addText("bogotobogo.com", QFont("Arial", 20) );
//    // movable text
//    text->setFlag(QGraphicsItem::ItemIsMovable);
}

void MainWindow::resizeEvent(QResizeEvent *event) {
    QSize size{event->size()};
    view_->setFixedSize(size.width(), size.height());
    view_->setSceneRect(0, 0, size.width(), size.height());
    view_->fitInView(0, 0, size.width(), size.height(), Qt::KeepAspectRatio);
}
