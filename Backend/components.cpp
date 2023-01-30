#include "circuitcomponent.h"

class ButtonComponent : public CircuitComponent {
public:

    ButtonComponent():
        CircuitComponent{0, 1},
        state_{false}
    {

    }

    virtual void run() override {
        pinOutArray_[0].setState(state_); // consider switching this to just a 1 output pin system, this is good for now but think about it and the pros/cons
    }

    void setState(bool state) {
        state_ = state;
    }

private:
    bool state_;
};

class CircuitIn : public CircuitComponent {
public:

    CircuitIn(int inSize):
        CircuitComponent{0, inSize}
    {

    }

    virtual void run() override {
        for (int i{}; i < outSize_; i++) { // outSize_ is set to inSize value due to nomenclature of CircuitComponent
            // IO Job
        }
    }

    void run(bool input[]) {
        for (int i{}; i < outSize_; i++) {
            pinOutArray_[i].setState(input[i]);
        }
    }

};

//class CircuitOut : public CircuitComponent {
//public:

//    CircuitOut(int outSize):
//        CircuitComponent{outSize}
//    {

//    }

//    virtual void run() override {
//        for (int i{}; i < outSize_; i++) { // outSize_ is set to inSize value due to nomenclature of CircuitComponent
//            // IO Job
//        }
//    }

//};
