#ifndef GATES_H
#define GATES_H


#include "circuitcomponent.h"
#include <iostream>

// move all to cpp file

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

    CircuitIO(int in_size, int out_size):
        CircuitComponent{in_size, out_size}
    {

    }

    virtual void run() override {
        for (int i{}; i < inSize_; i++) {
            std::cout << pinInArray_[i].state() << std::endl;
        }
    }

    void run(bool input[]) {
        for (int i{}; i < outSize_; i++) {
            pinOutArray_[i].setState(input[i]);
        }
    }

};

//class ButtonComponent : public CircuitComponent {
//public:

//    ButtonComponent():
//        CircuitComponent{1, 1}
//    {

//    }

//    virtual void run() override {
//        pinOutArray_[0].setState(pinInArray_[0].state()); // consider switching this to just a 1 output pin system, this is good for now but think about it and the pros/cons
//    }

//};

#endif // GATES_H
