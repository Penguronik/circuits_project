#ifndef GRAPHICSCIRCUITCOMPONENT_H
#define GRAPHICSCIRCUITCOMPONENT_H

//HEADERS
#include "Backend/circuitcomponent.h"
#include "body.h"
#include "graphicspinbase.h"

//QT
#include <QGraphicsItemGroup>
#include <QPainter>
#include <QList>

class GraphicsCircuitComponent : public QGraphicsItem
{
//    Q_OBJECT If you want to use q object properties, reinclude this and also inherit QGraphicsObject instead
public:

    // Qt Type
    enum{Type = UserType};
    virtual int type() const override { return Type; }

    // Constructors
    explicit GraphicsCircuitComponent(CircuitComponent *circuit, QGraphicsItem *parent = nullptr);

    // Getters
    virtual QRectF boundingRect() const override;
    virtual QPainterPath shape() const override;

    // Public Functions
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
    void generateInPins();
    void generateOutPins();

//    static void connect(GraphicsPinBase &graphicsPinIn, GraphicsPinBase &graphicsPinOut) { //Make all objects pass by reference wherever possible if theyre not already a pointer
//        CircuitComponent::connect(graphicsPinIn.pin(), graphicsPinOut.pin());
//    }

//    static void connect(GraphicsPinBase *graphicsPinIn, GraphicsPinBase *graphicsPinOut) {
//        connect(*graphicsPinIn, *graphicsPinOut);
//    }

//    void update();

    void updateStates();
    void updateWires();
    void run();
    void updatePinColors();

protected:
    Body *body_;
    QList<GraphicsPinIn*> *inPinList_;
    QList<GraphicsPinOut*> *outPinList_;
    CircuitComponent *circuitComponent_;

};

#endif // GRAPHICSCIRCUITCOMPONENT_H
