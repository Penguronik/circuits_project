//UTIL
#include "constants.h"

//QT
#include <QGraphicsItem>
#include <QtGui/qevent.h>

//HEADERS
#include "Backend/interface.h"
#include "Backend/gates.h"
#include "mainwindow.h"
#include "componentcontainer.h"


MainWindow::MainWindow(QWidget *parent):
    QWidget{parent},
    scene_{new QGraphicsScene{this}}, //Consider creating a class for the scene at a point if the MainWindow class instead inherits MainWindow and you add gui elements surrounding the scene in the middle, so its more grouped
    view_{new View(scene_, this)}
{
    scene_->setSceneRect(0, 0, constant::WIDTH, constant::HEIGHT);


    Interface *interface{new Interface{}};

//    Component *component_1{new Component{interface->newComponent()}}; //Component may be already used by qt?

    Circuit *circuit_1{new NOTGate{}};

    ComponentContainer *test{new ComponentContainer{circuit_1}};

    scene_->addItem(test);
    test->setX(200);
    test->setY(200);
    test->setFlag(QGraphicsItem::ItemIsMovable);





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
