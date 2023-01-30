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
#include <QSplitter>

#include <QPushButton>

//HEADERS
#include "mainwindow.h"


MainWindow::MainWindow(QWidget *parent):
    QMainWindow{parent},
    scene_{new Scene{this}},
    view_{new View(scene_, this)}
{

//    QFrame *frame = new QFrame{};
//    QHBoxLayout *frameLayout = new QHBoxLayout{frame};

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
    qDebug() << tree->font();
    tree->setFont(QFont{"Segoe UI", 9, -1});
    qDebug() << tree->font();
    qDebug() << tree->iconSize();
    tree->setIconSize(QSize{10, 10});
//    tree->

//    frameLayout->

    QSplitter *splitter = new QSplitter{this};
    splitter->addWidget(tree);
    splitter->addWidget(view_);
    splitter->setCollapsible(splitter->indexOf(view_), false);

    setCentralWidget(splitter);

//    frameLayout->addWidget(tree);
//    frameLayout->addWidget(view_);
//    setCentralWidget(frame);
//    view_->hide();
//    tree->show();

}
