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
        *outArray_[0] = !stateArray_[0];
        propogateAll();
    }
};

class ANDGate : public Circuit {
    public:
    ANDGate():
    Circuit{2,1}
        { }

    virtual void run() override {
        *outArray_[0] = stateArray_[0] && stateArray_[1];
        propogateAll();
    }

};

class ORGate : public Circuit {
    public:
        ORGate():
        Circuit{2,1} {
        }

        virtual void run() override {
            *outArray_[0] = stateArray_[0] || stateArray_[1];
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

        void run(int input[], int size) {
            assert(outSize_ == size);
            for (int i{}; i < size; i++) {
                *outArray_[i] = input[i];
            }
            propogateAll();
        }

};

#endif // GATES_H
