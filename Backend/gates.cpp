#include "circuitcomponent.h"
#include <iostream>
#include <QDebug>

class NOTGate : public CircuitComponent {
public:
    NOTGate():
        CircuitComponent{1, 1}
    {

    }

    virtual void run() override {

        pinOutArray_[0].setState(!pinInArray_[0].state());
    }
};

class ANDGate : public CircuitComponent {
public:
    ANDGate():
        CircuitComponent{2,1}
    {

    }

    virtual void run() override {
        pinOutArray_[0].setState(pinInArray_[0].state() && pinInArray_[1].state());
    }

};

class ORGate : public CircuitComponent {
public:
    ORGate():
        CircuitComponent{2,1}
    {

    }

    virtual void run() override {
        pinOutArray_[0].setState(pinInArray_[0].state() || pinInArray_[1].state());
    }

};

class CircuitIO : public CircuitComponent {
public:

    CircuitIO(int inSize, int outSize):
        CircuitComponent{inSize, outSize}
    {

    }

    virtual void run() override {
        for (int i{}; i < inSize_; i++) {
//            qDebug() << pinInArray_[i].state();
        }
    }

    void run(bool input[]) {
        for (int i{}; i < outSize_; i++) {
            pinOutArray_[i].setState(input[i]);
        }
    }

};
