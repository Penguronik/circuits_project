#ifndef MAINWINDOW_H
#define MAINWINDOW_H

//HEADERS
#include "componentcontainer.h"
#include "scene.h"
#include "view.h"

//QT
#include <QWidget>

class MainWindow : public QWidget //Consider switching to MainWindow class inheritance when adding GUI
{
//    Q_OBJECT  Probably a good idea to look over all classes and check for possible use of Q_OBJECT, take a look at the documentation one more time to see it's benefits including the properties and slots/signals

public:

    // Constructors
    //
    explicit MainWindow(QWidget *parent = nullptr);

    // Events
    //
    virtual void resizeEvent(QResizeEvent *event) override;

private:
    Scene *scene_;
    View *view_;
    QList<ComponentContainer*> *containerList_;
};
#endif // MAINWINDOW_H
