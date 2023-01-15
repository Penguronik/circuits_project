#ifndef GATES_H
#define GATES_H


#include "circuitcomponent.h"
#include <cassert>

// move all to cpp file

class NOTGate : public CircuitComponent {
    public:
        NOTGate():
            CircuitComponent{1, 1} {
        }

    virtual void run() override {

        pinOutArray_[0].set(!pinInArray_[0].state());
        propogateAll();
    }
};

class ANDGate : public CircuitComponent {
    public:
    ANDGate():
    CircuitComponent{2,1}
        { }

    virtual void run() override {
        pinOutArray_[0].set(pinInArray_[0].state() && pinInArray_[1].state());
        propogateAll();
    }

};

class ORGate : public CircuitComponent {
    public:
        ORGate():
        CircuitComponent{2,1} {
        }

        virtual void run() override {
            pinOutArray_[0].set(pinInArray_[0].state() || pinInArray_[1].state());
            propogateAll();
        }

};

class CircuitIO : public CircuitComponent {
    public:

        CircuitIO(int in_size, int out_size):
        CircuitComponent{in_size, out_size} {
        }

        virtual void run() override {
            for (int i{}; i < inSize_; i++) {
                std::cout << pinInArray_[i].state() << std::endl;
            }
        }

        void run(bool input[], int size) {
            std::cout << "hello";
            assert(outSize_ == size); // remove assert
            for (int i{}; i < size; i++) {
                std::cout << "hello";
                pinOutArray_[i].set(input[i]);
            }
            propogateAll();
        }

};

#endif // GATES_H
