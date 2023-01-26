#include "Backend/componenttreemodel.h"
#include "constants.h"
#include <iostream>

//QT
#include <QGraphicsItem>
#include <QtGui/qevent.h>
#include <QMenuBar>
#include <QToolBar>
#include <QHBoxLayout>
#include <QListView>
#include <QTreeView>

#include <QPushButton>

//HEADERS
#include "mainwindow.h"


MainWindow::MainWindow(QWidget *parent):
    QMainWindow{parent},
    scene_{new Scene{this}},
    view_{new View(scene_, this)},
    timer{}
{
    timer.start(15, this);
    scene_->setSceneRect(0, 0, 500, 500);

//    view_->setFixedSize(constant::WIDTH, constant::HEIGHT);
//    view_->setSceneRect(0, 0, constant::WIDTH, constant::HEIGHT);
//    view_->fitInView(0, 0, constant::WIDTH, constant::HEIGHT, Qt::KeepAspectRatio);


    for (int i{}; i < 2; i++){
        ORGate *circuit{new ORGate{}};
        GraphicsORGate *container{new GraphicsORGate{circuit}};
        std::cout << container << "<- container address";
        scene_->addComponent(container);
        scene_->addItem(container);
    }
    ANDGate *circuit{new ANDGate{}};
    GraphicsANDGate *container{new GraphicsANDGate{circuit}};
    std::cout << container << "<- container address";
    scene_->addComponent(container);
    scene_->addItem(container);

    NOTGate *circuit2{new NOTGate{}};
    GraphicsNOTGate *container2{new GraphicsNOTGate{circuit2}};
    std::cout << container2 << "<- container address";
    scene_->addComponent(container2);
    scene_->addItem(container2);

    NOTGate *circuit3{new NOTGate{}};
    GraphicsNOTGate *container3{new GraphicsNOTGate{circuit3}};
    std::cout << container3 << "<- container address";
    scene_->addComponent(container3);
    scene_->addItem(container3);

    std::cout << "test";

    CircuitIO *IO{new CircuitIO{1,2}};
    GraphicsCircuitIO *GraphicsIO{new GraphicsCircuitIO{IO}};
    scene_->addItem(GraphicsIO);
    GraphicsIO->generatePins();
    IO_ = IO;
    GraphicsIO_ = GraphicsIO;

    for (int i{}; i < 2; i++){
        ButtonComponent *button{new ButtonComponent{}};
        GraphicsButtonComponent *graphicsButton{new GraphicsButtonComponent{button}};
        scene_->addItem(graphicsButton);
        scene_->addComponent(graphicsButton);
    }




    QFrame *frame = new QFrame{};
    QHBoxLayout *frameLayout = new QHBoxLayout{frame};

    ComponentTreeModel *model {new ComponentTreeModel{}};

    QTreeView *tree{new QTreeView{}};
//    tree.setAnimated(true);
//    tree.setIndentation(20);
//    tree.setAcceptDrops(true);
//    tree.setDropIndicatorShown(true);
//    tree.setDragEnabled(true);
//    const QSize availableSize = tree.screen()->availableGeometry().size();
//    tree.resize(availableSize/2);
//    tree.setColumnWidth(0, tree.width() / 3);
    tree->setModel(model);
    tree->setHeaderHidden(true);
    tree->setDragDropMode(QAbstractItemView::DragOnly);
    tree->setSelectionMode(QAbstractItemView::SingleSelection);
    tree->setDragEnabled(true);
    tree->setAcceptDrops(true);
    tree->setDropIndicatorShown(true);




//    QListView *piecesList = new QListView;
//    piecesList->setDragEnabled(true);
//    piecesList->setViewMode(QListView::ListMode);
//    piecesList->setMovement(QListView::Snap);

//    piecesList->setViewMode(QListView::IconMode);
//    piecesList->setIconSize(QSize(puzzleWidget->pieceSize() - 20, puzzleWidget->pieceSize() - 20));
//    piecesList->setGridSize(QSize(puzzleWidget->pieceSize(), puzzleWidget->pieceSize()));
//    piecesList->setSpacing(10);
//    piecesList->setMovement(QListView::Snap);
//    piecesList->setAcceptDrops(true);
//    piecesList->setDropIndicatorShown(true);

    frameLayout->addWidget(tree);
    frameLayout->addWidget(view_);
    setCentralWidget(frame);
//    view_->hide();
//    tree->show();



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
    std::cout<< event->size().height() << "h" << event->size().width() << "w" << std::endl;
    QSize size{event->size()};
    view_->setFixedSize(500, 500);
    view_->setSceneRect(0, 0, 500, 500);
    view_->fitInView(0, 0, 500, 500, Qt::KeepAspectRatio);
}

void MainWindow::keyPressEvent(QKeyEvent *event) {
    if (event->key() == Qt::Key_Space) {
        bool circuitInput[2]{true, false};
        IO_->run(circuitInput);
        QList<GraphicsCircuitComponent*>::const_iterator i{};
        for (i = scene_->componentList().constBegin(); i != scene_->componentList().constEnd(); ++i) {
            (*i)->updateStates();
            IO_->updateStates();
        }
        for (i = scene_->componentList().constBegin(); i != scene_->componentList().constEnd(); ++i) {
            (*i)->run();
        }
        for (i = scene_->componentList().constBegin(); i != scene_->componentList().constEnd(); ++i) {
            (*i)->updateWires();
            IO_->updateWires();
        }
        for (i = scene_->componentList().constBegin(); i != scene_->componentList().constEnd(); ++i) {
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
    for (i = scene_->componentList().constBegin(); i != scene_->componentList().constEnd(); ++i) {
        (*i)->updateStates();
        IO_->updateStates();
    }
    for (i = scene_->componentList().constBegin(); i != scene_->componentList().constEnd(); ++i) {
        (*i)->run();
    }
    for (i = scene_->componentList().constBegin(); i != scene_->componentList().constEnd(); ++i) {
        (*i)->updateWires();
        IO_->updateWires();
    }
    for (i = scene_->componentList().constBegin(); i != scene_->componentList().constEnd(); ++i) {
        (*i)->updatePinColors();
    }
    std::cout << "Output: " << IO_->pinInArray()->state() << std::endl;
}
