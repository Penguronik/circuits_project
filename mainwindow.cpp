#include "mainwindow.h"
#include <QGraphicsItem>
#include "componentgroup.h"
#include "qevent.h"

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent),
    scene{new QGraphicsScene{this}}
{
    scene->setSceneRect(0,0,500,500);
    view = new View(this);
    view->setScene(scene);
    view->setFixedSize(500, 500);
    view->setSceneRect(0, 0, 500, 500);
    view->fitInView(0, 0, 500, 500, Qt::KeepAspectRatio);
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ComponentGroup *test = new ComponentGroup{};
    scene->addItem(test);
    test->setHandlesChildEvents(false); //doing this for now, might me a better idea to switch to having
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
    QSize size = event->size();
    view->setFixedSize(size.width(), size.height());
    view->setSceneRect(0, 0, size.width(), size.height());
    view->fitInView(0, 0, size.width(), size.height(), Qt::KeepAspectRatio);
}
