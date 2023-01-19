#include "circuitcomponent.h"

CircuitComponent::CircuitComponent(int inSize, int outSize):
    inSize_{inSize},
    outSize_{outSize},
    pinInArray_{new PinIn[inSize_]{}},
    pinOutArray_{new PinOut[outSize_]{}}
{
    for (int i{0}; i < inSize_; i++) {
        pinInArray_[i].setParentCircuitComponent(this);
    }

    for (int j{0}; j < outSize_; j++) {
        pinOutArray_[j].setParentCircuitComponent(this);
    }
}

CircuitComponent::~CircuitComponent(){
    delete[] pinInArray_;
    delete[] pinOutArray_;
}

void CircuitComponent::updateStates() {
    for (int i{0}; i < inSize_; i++) {
        pinInArray_[i].updateState();
    }
}

void CircuitComponent::updateWires() {
    for (int i{0}; i < outSize_; i++) {
        pinOutArray_[i].updateWire();
    }

}

int CircuitComponent::inSize() const
{
    return inSize_;
}

int CircuitComponent::outSize() const
{
    return outSize_;
}

PinIn *CircuitComponent::pinInArray() const {
    return pinInArray_;
}
PinOut *CircuitComponent::pinOutArray() const {
    return pinOutArray_;
}

