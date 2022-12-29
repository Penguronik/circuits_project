#ifndef MAINWINDOW_H
#define MAINWINDOW_H

//HEADERS
#include "view.h"

//QT
#include <QWidget>

class MainWindow : public QWidget //Consider switching to MainWindow class inheritance when adding GUI
{
//    Q_OBJECT  Probably a good idea to look over all classes and check for possible use of Q_OBJECT, take a look at the documentation one more time to see it's benefits including the properties and slots/signals

public:
    explicit MainWindow(QWidget *parent = nullptr);
    virtual void resizeEvent(QResizeEvent *event) override;

private:
    QGraphicsScene *scene_;
    View *view_;
};
#endif // MAINWINDOW_H
