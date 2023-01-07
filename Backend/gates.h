#ifndef GATES_H
#define GATES_H


#include "circuit.h"
#include <cassert>

class NOTGate : public Circuit {
    public:
        NOTGate():
            Circuit{1, 1} {
        }

    virtual void run() override {

        pinOutArray_[0].set(!pinInArray_[0].state());
        propogateAll();
    }
};

class ANDGate : public Circuit {
    public:
    ANDGate():
    Circuit{2,1}
        { }

    virtual void run() override {
        pinOutArray_[0].set(pinInArray_[0].state() && pinInArray_[1].state());
        propogateAll();
    }

};

class ORGate : public Circuit {
    public:
        ORGate():
        Circuit{2,1} {
        }

        virtual void run() override {
            pinOutArray_[0].set(pinInArray_[0].state() || pinInArray_[1].state());
            propogateAll();
        }

};

class Board : public Circuit {
    public:

        Board(int in_size, int out_size):
        Circuit{in_size, out_size} {
        }

        virtual void run() override {
        }

        void run(bool input[], int size) {
//            std::cout << "hello";
            assert(outSize_ == size);
            for (int i{}; i < size; i++) {
                std::cout << "hello";
                pinOutArray_[i].set(input[i]);
            }
            propogateAll();
        }

};

#endif // GATES_H
