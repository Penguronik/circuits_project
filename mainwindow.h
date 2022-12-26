#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "view.h"
#include "pin.h"

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    virtual void resizeEvent(QResizeEvent *event) override;

private:
    QGraphicsScene *scene;
    View *view;
    Pin *ellipse;
    QGraphicsRectItem *rectangle;
    QGraphicsTextItem *text;
};
#endif // MAINWINDOW_H
