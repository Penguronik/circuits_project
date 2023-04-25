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

class XORGate : public CircuitComponent {
public:
    XORGate():
        CircuitComponent{2,1}
    {

    }

    virtual void run() override {
        pinOutArray_[0].setState(pinInArray_[0].state() ^ pinInArray_[1].state());
    }

};
